#include <QApplication>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QCheckBox>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QPushButton>

class SalaryDelegate : public QStyledItemDelegate
{
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        if (index.data().toInt() <= 2000)
            painter->fillRect(option.rect, Qt::red);
        QStyledItemDelegate::paint(painter, option, index);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Set up the model
    QStandardItemModel model;
    model.setHorizontalHeaderLabels({"Sicil No", "İsim", "Soyisim", "Teknik Personel", "Maaş", "Departman"});
    model.appendRow({new QStandardItem("1"), new QStandardItem("Ayşe"), new QStandardItem("Sarı"), new QStandardItem("True"), new QStandardItem("3000"), new QStandardItem("Yazılım")});
    model.appendRow({new QStandardItem("2"), new QStandardItem("Bilge"), new QStandardItem("Güneş"), new QStandardItem("False"), new QStandardItem("1500"), new QStandardItem("İnsan Kaynakları")});
    model.appendRow({new QStandardItem("3"), new QStandardItem("Cemal"), new QStandardItem("Vahitoğlu"), new QStandardItem("True"), new QStandardItem("2500"), new QStandardItem("Pazarlama")});
    model.appendRow({new QStandardItem("4"), new QStandardItem("Deniz"), new QStandardItem("Batı"), new QStandardItem("False"), new QStandardItem("2000"), new QStandardItem("Finans")});
    model.appendRow({new QStandardItem("5"), new QStandardItem("Enes"), new QStandardItem("Kanter"), new QStandardItem("True"), new QStandardItem("3000"), new QStandardItem("Yazılım")});

    // Set up the "Add" button
    QPushButton addButton;
    addButton.setText("Add");
    QObject::connect(&addButton, &QPushButton::clicked, [&model]() {
        // Set up the form to enter the personnel information
        QLineEdit sicilNoEdit;
        QLineEdit isimEdit;
        QLineEdit soyisimEdit;
        QCheckBox teknikPersonelCheckBox;
        QLineEdit maasEdit;
        QLineEdit departmanEdit;

        // Create a new row in the model
        int row = model.rowCount();
        model.insertRow(row);

        // Set the values of the new row using the form data
        model.setData(model.index(row, 0), sicilNoEdit.text().toInt());
        model.setData(model.index(row, 1), isimEdit.text());
        model.setData(model.index(row, 2), soyisimEdit.text());
        model.setData(model.index(row, 3), teknikPersonelCheckBox.isChecked());
        model.setData(model.index(row, 4), maasEdit.text().toInt());
        model.setData(model.index(row, 5), departmanEdit.text());
    });


    // Set up the proxy model
    QSortFilterProxyModel proxyModel;
    proxyModel.setSourceModel(&model);

    // Set up the table view
    QTableView tableView;
    tableView.setModel(&proxyModel);
    tableView.setSortingEnabled(true);
    tableView.setAlternatingRowColors(true);
    tableView.horizontalHeader()->setStretchLastSection(true);
    tableView.verticalHeader()->setVisible(false);
    tableView.setItemDelegateForColumn(4, new SalaryDelegate);
    tableView.setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView.setSelectionMode(QAbstractItemView::SingleSelection);

    // Set up the search box
    QLineEdit searchBox;
    QObject::connect(&searchBox, &QLineEdit::textChanged, [&proxyModel](const QString &text) {
        QRegExp regExp(text, Qt::CaseInsensitive, QRegExp::Wildcard);
        proxyModel.setFilterKeyColumn(-1);
        proxyModel.setFilterRegExp(regExp);
    });
    searchBox.setPlaceholderText("Metin tabanlı arama...");


    // Set up the "hide administrative personnel" checkbox
    QCheckBox hideAdminCheckBox;
    hideAdminCheckBox.setText("Idari personeli gizle");
    QObject::connect(&hideAdminCheckBox, &QCheckBox::stateChanged, [&proxyModel](int state) {
        proxyModel.setFilterKeyColumn(-1);
        proxyModel.setFilterRegExp(state == Qt::Checked ? QRegExp("False") : QRegExp());
    });

    // Set up the layout
    QVBoxLayout mainLayout;
    mainLayout.addWidget(&searchBox);
    mainLayout.addWidget(&addButton);
    mainLayout.addWidget(&hideAdminCheckBox);
    mainLayout.addWidget(&tableView);

    // Set up the main window
    QWidget window;
    window.setLayout(&mainLayout);
    window.setWindowTitle("Personel Yönetimi");
    window.setGeometry(100, 100, 750, 450);
    window.show();

    return app.exec();
}
