# Staff Management App
Basic Staff Management application. 

My main purpose to implement this is to learn QSortFilterProxyModel structure
and gain knowledge about modern cpp, especially lambda functions in this project.

This code is a simple example of how to use a QTableView in Qt to display data in a table format, and how to use a QSortFilterProxyModel to filter the data in the table based on user input. The code also demonstrates the use of a custom delegate, the SalaryDelegate, to change the background color of cells in the "Salary" column that have a value less than or equal to 2000.

## TableView

The QTableView is created and its model is set to the proxy model. The _setSortingEnabled()_ method is used to allow the user to sort the data by clicking on the table headers, _setAlternatingRowColors()_ method is used to give an alternate background color to the rows. The _horizontalHeader()_ and _verticalHeader()_ methods are used to customize the appearance of the table headers, and the _setItemDelegateForColumn()_ method is used to set the custom delegate for the "Salary" column.

## SortFilterProxyModel

The QSortFilterProxyModel is used to filter the data in the table based on user input. The _setSourceModel()_ method is used to set the source model for the proxy model, and the _setFilterKeyColumn()_ and _setFilterRegExp()_ methods are used to set the column to be filtered and the regular expression used for the filtering, respectively.

## SalaryDelegate

The SalaryDelegate is a custom delegate that inherits from QStyledItemDelegate. The _paint()_ method is overridden to change the background color of cells in the "Salary" column that have a value less than or equal to 2000.

## Add button

A QPushButton is created to add new rows to the table. The clicked signal is connected to a lambda function that creates form for the user to enter new personnel information.

## SearchBox

A QLineEdit is created to allow the user to search the table for specific personnel. The textChanged signal is connected to a lambda function that sets the search term in the proxyModel.

## Layouts

The widgets are placed in a _QHBoxLayout_ and _QVBoxLayout_ to get the desired layout.

## Running the code

To run the code, you will need to have Qt installed on your system. You can then build and run the code using the Qt Creator IDE, or by using the qmake tool to generate a Makefile and then running make.

The next step is to create the layouts for the widgets. You can use a _QVBoxLayout_ to arrange the widgets vertically, with the table view taking up the most space, and the other widgets stacked on top of each other above it. You can also use a _QHBoxLayout_ to arrange the search box and the "Add" button horizontally.

Here's an example of how you might set up the layouts:

```C++
    // Set up the main layout
    QVBoxLayout mainLayout;
    mainLayout.addWidget(&searchBox);
    mainLayout.addWidget(&tableView);
    mainLayout.addWidget(&addButton);

    // Create the main window
    QWidget window;
    window.setLayout(&mainLayout);
    window.show();

    return app.exec();
```

In this example, the search box and "Add" button are added to the top of the main layout, and the table view is added below them. The main layout is then set as the layout for the main window, and the window is displayed.

You can also set the size and position of the window, set the window title, etc.

Finally, the _app.exec()_ function is called to start the event loop and enter the main loop of the application. This causes the application to wait for user input, and process events such as mouse clicks, key presses, and window resizing. The event loop exits when the user closes the main window or exits the application.

This is just an example of how you might set up a simple table view with sorting and filtering. You can customize the appearance of the table view and its items using stylesheets, and you can add other features such as editing and deleting rows.
