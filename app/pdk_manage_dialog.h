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

class PdkManageDialog final: public QDialog
{
    Q_OBJECT
public:
    explicit PdkManageDialog(QWidget *parent = nullptr);
    ~PdkManageDialog(void) override;

protected:
    // void closeEvent(QCloseEvent *event) override;

private slots:
    // void accept();
    void onListItemClicked(const QModelIndex &index);
    void onAddPushButtonClicked(void);
    void onDelPushButtonClicked(void);
    void onSaveStyleInfo(void);
    void onStyleFrameChanged(const BorderStyle &style);
    void onLayerNameFinished(void);
    void onGdsNumberNameFinished(void);
    void onDataTypeFinished(void);
private:
    int parseCfgFile(const QString &file);
    int writeCfgFile(const QString &filename);
    void setupUi();

private:
    QList<PdkInfo> m_pdk_info_list;
    // QListWidget *m_listWidget;
    QListView *mp_list_view;
    // QTextEdit *m_contentTextEdit;
    // PdkItemModel *m_pdkItemModel;
    PdkListModel *mp_pdk_list_model;
    QLineEdit *mp_layername_line_edit;
    QLineEdit *mp_gdsnumber_line_edit;
    QLineEdit *mp_datatype_line_edit;
    StyleFrame *mp_style_frame;
    QModelIndex m_custom_index;
};

#endif // PDK_MANAGE_DIALOG_H
