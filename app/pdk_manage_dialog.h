#ifndef PDK_MANAGE_DIALOG_H
#define PDK_MANAGE_DIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QListWidget>
#include <QTextEdit>
#include <QTableView>
#include <QFrame>
#include "pdk_info.h"
#include "pdkitemmodel.h"
#include "pdklistmodel.h"
#include "editableitemdelegate.h"
#include "styleframe.h"

class PdkManageDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PdkManageDialog(QWidget *parent = nullptr);
    ~PdkManageDialog();

protected:
    // void closeEvent(QCloseEvent *event) override;

private slots:
    // void accept();
    void onListItemClicked(const QModelIndex &index);
    void onAddPushButtonClicked();
    void onDelPushButtonClicked();
    void onSaveStyleInfo();
    void onStyleFrameChanged(const BorderStyle &style);
    void onLayerNameFinished();
    void onGdsNumberNameFinished();
    void onDataTypeFinished();
private:
    int ParseCfgFile(const QString &file);
    int WriteCfgFile(const QString &filename);
    void SetupUi();

private:
    QList<PdkInfo> m_pdk_info_list;
    // QListWidget *m_listWidget;
    QListView *mp_list_view;
    // QTextEdit *m_contentTextEdit;
    // PdkItemModel *m_pdkItemModel;
    PdkListModel *mp_pdk_list_model;
    QLineEdit *mp_layername_lineedit;
    QLineEdit *mp_gdsnumber_lineedit;
    QLineEdit *mp_datatype_lineedit;
    StyleFrame *mp_style_frame;
    QModelIndex m_custom_index;
};

#endif // PDK_MANAGE_DIALOG_H
