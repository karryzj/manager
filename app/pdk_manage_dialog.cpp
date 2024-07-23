#include <QBoxLayout>
#include <QContextMenuEvent>
#include <QInputDialog>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <algorithm>
#include <QGroupBox>
#include "pdk_manage_dialog.h"
#include "listitemwidget.h"

PdkManageDialog::PdkManageDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("图层管理");
    int ret = parseCfgFile("D:\\Work\\pdk_manager\\pdk.json");
    Q_ASSERT(ret == 0);

    setupUi();
}

void PdkManageDialog::onListItemClicked(const QModelIndex &index)
{
    // 根据左侧列表项的选择更新右侧内容
    m_custom_index = index;
    QString selected_item = index.data().toString();
    auto it = std::find_if(m_pdk_info_list.begin(), m_pdk_info_list.end(), [&](const PdkInfo &pdk_info)
    {
        return pdk_info.layer_name == selected_item;
    });
    if (it != m_pdk_info_list.end())
    {
        mp_layername_line_edit->setText(selected_item);

        mp_gdsnumber_line_edit->setText(QString::number(it->gds_number));
        mp_datatype_line_edit->setText(QString::number(it->data_type));
        mp_style_frame->setStyle(it->style);
        mp_style_frame->update();
        // mp_style_frame->setFrameShape(QFrame::Box);
        // mp_style_frame->setFrameShadow(QFrame::Raised);
        // mp_style_frame->setLineWidth(2);
        // mp_style_frame->setMidLineWidth(3);  // 设置中间线宽度，如果需要的话

        // 设置 QFrame 的填充颜色
        // mp_style_frame->setStyleSheet("background-color: lightblue;");
    }

    // m_layerNameLineEdit->setText(selectedItem);
    // m_contentTextEdit->setText(selectedItem);
}

void PdkManageDialog::onAddPushButtonClicked()
{
    // Insert item at the current index or at the end if no index is selected
    QModelIndex index = mp_list_view->currentIndex();
    int row = index.isValid() ? mp_pdk_list_model->rowCount() : index.row();
    mp_pdk_list_model->insertRows(row, 1);
    QString text = QString("%1%2").arg("Metal").arg(row+100);
    mp_pdk_list_model->setData(mp_pdk_list_model->index(row), text);
    mp_layername_line_edit->setText(text);
    PdkInfo pdk_info;
    pdk_info.layer_name = text;
    pdk_info.gds_number = 0;
    pdk_info.data_type = 0;
    pdk_info.style = {0};
    m_pdk_info_list.append(pdk_info);
}

void PdkManageDialog::onDelPushButtonClicked()
{
    if (m_custom_index.isValid())
    {
        auto var = mp_pdk_list_model->data(m_custom_index);
        QString custom_layer_name(var.toString());

        auto it = std::find_if(m_pdk_info_list.begin(), m_pdk_info_list.end(), [&](const PdkInfo &item)
        {
            return item.layer_name == custom_layer_name;
        });
        if (it != m_pdk_info_list.end())
        {
            m_pdk_info_list.removeAll(*it);
            // mp_pdk_list_model->setData(m_custom_index, text);
            // emit mp_pdk_list_model->dataChanged(m_custom_index, m_custom_index);
        }
        // 删除选中的项
        mp_pdk_list_model->removeItem(m_custom_index.row());
    }
}

void PdkManageDialog::onSaveStyleInfo()
{
    writeCfgFile("D:\\Work\\pdk_manager\\pdk.json");
}

void PdkManageDialog::onStyleFrameChanged(const BorderStyle &style)
{
    if (m_custom_index.isValid())
    {
        auto var = mp_pdk_list_model->data(m_custom_index);
        QString custom_layer_name(var.toString());

        auto it = std::find_if(m_pdk_info_list.begin(), m_pdk_info_list.end(), [&](const PdkInfo &item)
        {
            return item.layer_name == custom_layer_name;
        });
        if (it != m_pdk_info_list.end())
        {
            it->style = style;
        }
    }
}

void PdkManageDialog::onLayerNameFinished()
{
    QString text = mp_layername_line_edit->text();
    if (m_custom_index.isValid())
    {
        auto var = mp_pdk_list_model->data(m_custom_index);
        QString custom_layer_name(var.toString());
        if (text != custom_layer_name)
        {
            auto it = std::find_if(m_pdk_info_list.begin(), m_pdk_info_list.end(), [&](const PdkInfo &item)
            {
                return item.layer_name == custom_layer_name;
            });
            if (it != m_pdk_info_list.end())
            {
                it->layer_name = text;
                mp_pdk_list_model->setData(m_custom_index, text);
                emit mp_pdk_list_model->dataChanged(m_custom_index, m_custom_index);
            }
        }
    }
}

void PdkManageDialog::onGdsNumberNameFinished()
{
    if (m_custom_index.isValid())
    {
        auto var = mp_pdk_list_model->data(m_custom_index);
        QString custom_layer_name(var.toString());

        auto it = std::find_if(m_pdk_info_list.begin(), m_pdk_info_list.end(), [&](const PdkInfo &item)
        {
            return item.layer_name == custom_layer_name;
        });
        if (it != m_pdk_info_list.end())
        {
            QString text = mp_gdsnumber_line_edit->text();
            it->gds_number = text.toInt();
        }
    }
}

void PdkManageDialog::onDataTypeFinished()
{
    if (m_custom_index.isValid())
    {
        auto var = mp_pdk_list_model->data(m_custom_index);
        QString custom_layer_name(var.toString());

        auto it = std::find_if(m_pdk_info_list.begin(), m_pdk_info_list.end(), [&](const PdkInfo &item)
        {
            return item.layer_name == custom_layer_name;
        });
        if (it != m_pdk_info_list.end())
        {
            QString text = mp_datatype_line_edit->text();
            it->data_type = text.toInt();
        }
    }
}

// void PdkManageDialog::editItem(const QModelIndex &index)
// {
//     if (index.isValid()) {
//         QString currentItem = index.data(Qt::DisplayRole).toString();
//         m_listView->edit(index);
//         m_pdkListModel->setData(index, currentItem, Qt::EditRole);
//     }
//     // qDebug() << "Edit trigger set to:" << m_listView->editTriggers();
// }

int PdkManageDialog::parseCfgFile(const QString &filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file:" << filename;
        return -1;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError)
    {
        qDebug() << "Failed to parse JSON:" << parseError.errorString();
        return -1;
    }

    if (!doc.isObject())
    {
        qDebug() << "JSON document is not an object.";
        return -1;
    }

    QJsonObject jsonObject = doc.object();

    if (!jsonObject.contains("pdk") || !jsonObject["pdk"].isArray())
    {
        qWarning() << "Invalid JSON structure - 'pdk' array not found or not an array.";
        return -1;
    }

    QJsonArray pdk_array = jsonObject["pdk"].toArray();

    // Iterate through the array
    for (int i = 0; i < pdk_array.size(); ++i)
    {
        PdkInfo pdk_info;
        QJsonObject pdk_obj = pdk_array[i].toObject();
        pdk_info.layer_name = pdk_obj["layerName"].toString();
        pdk_info.gds_number = pdk_obj["gdsNumber"].toInt();
        pdk_info.data_type = pdk_obj["dataType"].toInt();
        // Access style object
        QJsonObject style_obj = pdk_obj["style"].toObject();
        pdk_info.style.border_line = style_obj["borderLine"].toInt();
        pdk_info.style.border_color = style_obj["borderColor"].toString().toInt(nullptr, 16);
        pdk_info.style.fill_line = style_obj["fillLine"].toInt();
        pdk_info.style.fill_color = style_obj["fillColor"].toString().toInt(nullptr, 16);
        m_pdk_info_list.append(pdk_info);
    }
    return 0;
}

int PdkManageDialog::writeCfgFile(const QString &filename)
{
    QJsonObject root_object;
    QJsonArray pdk_info_array;

    foreach (const PdkInfo &info, m_pdk_info_list)
    {
        QJsonObject pdk_object;
        pdk_object["layerName"] = info.layer_name;
        pdk_object["gdsNumber"] = info.gds_number;
        pdk_object["dataType"] = info.data_type;

        QJsonObject style_object;
        style_object["borderLine"] = info.style.border_line;
        style_object["borderColor"] = QString("0x%1").arg(info.style.border_color, 6, 16, QLatin1Char('0'));
        style_object["fillLine"] = info.style.fill_line;
        style_object["fillColor"] = QString("0x%1").arg(info.style.fill_color, 6, 16, QLatin1Char('0'));
        pdk_object["style"] = style_object;

        pdk_info_array.append(pdk_object);
    }
    root_object["pdk"] = pdk_info_array;

    QJsonDocument doc(root_object);

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file.");
        return -1;
    }

    file.write(doc.toJson());
    file.close();
    return 0;
}

void PdkManageDialog::setupUi()
{
    QStringList model_data;
    for (const auto &val : m_pdk_info_list)
    {
        model_data.append(val.layer_name);
    }
    mp_list_view = new QListView(this);
    // m_contentTextEdit = new QTextEdit(this);
    mp_pdk_list_model = new PdkListModel(this);
    mp_pdk_list_model->setData(model_data);
    // 添加左侧列表项
    mp_list_view->setModel(mp_pdk_list_model);

    // Set custom frames for each item
    for (int row = 0; row < mp_pdk_list_model->rowCount(); ++row)
    {
        QModelIndex index = mp_pdk_list_model->index(row);
        QString text = mp_pdk_list_model->data(index, Qt::DisplayRole).toString();
        BorderStyle style;
        auto it = std::find_if(m_pdk_info_list.begin(), m_pdk_info_list.end(), [&](const auto &pdk_info)
        {
            return pdk_info.layer_name == text;
        });
        if (it != m_pdk_info_list.end())
        {
            ListItemWidget *itemWidget = new ListItemWidget(it->style, text);
            mp_list_view->setIndexWidget(index, itemWidget);
        }
    }

    QHBoxLayout *leftBottomLayout = new QHBoxLayout();
    QPushButton *addPushButton = new QPushButton("添加");
    connect(addPushButton, &QPushButton::clicked, this, &PdkManageDialog::onAddPushButtonClicked);
    QPushButton *delPushButton = new QPushButton("删除");
    connect(delPushButton, &QPushButton::clicked, this, &PdkManageDialog::onDelPushButtonClicked);
    leftBottomLayout->addWidget(addPushButton);
    leftBottomLayout->addWidget(delPushButton);

    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->addWidget(mp_list_view);
    leftLayout->addLayout(leftBottomLayout);

    QGroupBox *groupbox = new QGroupBox();
    groupbox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    groupbox->setMaximumSize(350, 300);
    // groupbox->setFixedSize(350, 200);
    // 右上
    QLabel *label1 = new QLabel("Layer Name:");
    QLabel *label2 = new QLabel("GDS Number:");
    QLabel *label3 = new QLabel("Data Type:");
    QLabel *label4 = new QLabel("Style:");
    mp_layername_line_edit = new QLineEdit();
    mp_gdsnumber_line_edit = new QLineEdit();
    mp_datatype_line_edit = new QLineEdit();
    mp_style_frame = new StyleFrame();
    mp_style_frame->setMaximumSize(200, 50);
    mp_style_frame->setFixedSize(200, 50);

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addWidget(label1, 0, 0);
    gridLayout->addWidget(mp_layername_line_edit, 0, 2);
    gridLayout->addWidget(label2, 1, 0);
    gridLayout->addWidget(mp_gdsnumber_line_edit, 1, 2);
    gridLayout->addWidget(label3, 2, 0);
    gridLayout->addWidget(mp_datatype_line_edit, 2, 2);
    gridLayout->addWidget(label4, 3, 0);
    gridLayout->addWidget(mp_style_frame, 3, 2);

    // QVBoxLayout *rightTopLayout = new QVBoxLayout();

    groupbox->setLayout(gridLayout);


    // 右下
    QLabel *label5 = new QLabel("物理特性1:");
    QLabel *label6 = new QLabel("物理特性2:");
    QLabel *label7 = new QLabel("物理特性3:");
    QLabel *label8 = new QLabel("物理特性4:");

    QLineEdit *name1LineEdit = new QLineEdit();
    QLineEdit *value1LineEdit = new QLineEdit();
    QLineEdit *name2LineEdit = new QLineEdit();
    QLineEdit *value2LineEdit = new QLineEdit();
    QPushButton *addButton = new QPushButton("Add");
    QPushButton *saveButton = new QPushButton("Save All");

    QGridLayout *bottomGridLayout = new QGridLayout();
    bottomGridLayout->addWidget(label5, 0, 0);
    bottomGridLayout->addWidget(name1LineEdit, 0, 1);
    bottomGridLayout->addWidget(label6, 0, 2);
    bottomGridLayout->addWidget(value1LineEdit, 0, 3);
    bottomGridLayout->addWidget(label7, 1, 0);
    bottomGridLayout->addWidget(name2LineEdit, 1, 1);
    bottomGridLayout->addWidget(label8, 1, 2);
    bottomGridLayout->addWidget(value2LineEdit, 1, 3);
    bottomGridLayout->addWidget(addButton, 4, 2);
    bottomGridLayout->addWidget(saveButton, 4, 3);

    QGroupBox *groupbox_bottom = new QGroupBox();
    groupbox_bottom->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    groupbox_bottom->setMaximumSize(400, 300);
    groupbox_bottom->setLayout(bottomGridLayout);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(groupbox);
    rightLayout->setAlignment(groupbox, Qt::AlignTop);
    rightLayout->addSpacing(10);
    rightLayout->addWidget(groupbox_bottom);
    // rightLayout->addLayout(bottomGridLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    connect(mp_list_view, &QAbstractItemView::clicked, this, &PdkManageDialog::onListItemClicked);
    connect(mp_layername_line_edit, &QLineEdit::editingFinished, this, &PdkManageDialog::onLayerNameFinished);
    connect(mp_gdsnumber_line_edit, &QLineEdit::editingFinished, this, &PdkManageDialog::onGdsNumberNameFinished);
    connect(mp_datatype_line_edit, &QLineEdit::editingFinished, this, &PdkManageDialog::onDataTypeFinished);
    connect(mp_style_frame, &StyleFrame::dataChanged, this, &PdkManageDialog::onStyleFrameChanged);
    connect(saveButton, &QPushButton::clicked, this, &PdkManageDialog::onSaveStyleInfo);
    resize(480, 400);
    setWindowIcon(QIcon(":/img/13.png"));
}

// void PdkManageDialog::closeEvent(QCloseEvent *event)
// {
//     // 在Dialog关闭时执行的操作
//     // int ret = WriteCfgFile("D:\\Work\\pdk_manager\\pdk_test.json");

//     // 调用基类的closeEvent处理函数，确保正常的Dialog关闭行为
//     QDialog::closeEvent(event);
// }

PdkManageDialog::~PdkManageDialog()
{
    delete mp_list_view;
    delete mp_pdk_list_model;
    // delete m_delegate;
}

// void PdkManageDialog::accept()
// {
//     // 处理确认按钮的逻辑
//     QDialog::accept();
// }
