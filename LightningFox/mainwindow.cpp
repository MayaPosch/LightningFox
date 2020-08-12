#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <curl/curl.h>

#include <iostream>
#include <string>

#include <QStandardItemModel>
#include <QStandardItem>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    
    // Setup menu connections.
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit()));
    
    // Open SQLite database file.
	if (sqlite3_open("settings.db", &settings) != SQLITE_OK) {
		std::cerr << "Error opening settings database." << std::endl;
		sqlite3_close(settings);
		return;
	}
	
	// If this is the first run, create the necessary tables in the database.
	std::string query = "CREATE TABLE IF NOT EXISTS accounts (id INTEGER PRIMARY KEY AUTOINCREMENT \
						, name TEXT NOT NULL, type INTEGER NOT NULL, server TEXT, smtp TEXT, \
						user TEXT, pass TEXT)";
	char* errmsg = 0;
	if (sqlite3_exec(settings, query.c_str(), 0, 0, &errmsg) != SQLITE_OK) {
		std::cerr << "SQL error: " << errmsg << std::endl;
		sqlite3_free(errmsg);
		sqlite3_close(settings);
		return;
	}
    
    // Read in account and folder information. Create sidebar view, restore last open folder and
    // email.
	updateFolderList();
	updateEmailList();
    
    // Perform synchronisation on remote accounts if enabled.
    syncEmail();
}

MainWindow::~MainWindow() {
    delete ui;
	
	// Close database handles.
	if (settings) {
		sqlite3_close(settings);
	}
}


// --- UPDATE FOLDER LIST ---
// Update the sidebar view (default) with the list of folders.
bool MainWindow::updateFolderList() {
	// For each account, create a root item in the sidebar, then attach the account's folders to it.
	QStandardItemModel model;
	QStandardItem* parentItem = model.invisibleRootItem();
	
	std::string query;
	query = "SELECT id, name FROM accounts";
	if (sqlite3_exec(settings, query.c_str(), &MainWindow::processAccountEntries, (void*) parentItem, &errmsg) != SQLITE_OK) {
		std::cerr << "SQL error: " << errmsg << std::endl;
		sqlite3_free(errmsg);
		sqlite3_close(settings);
		return false;
	}
	
	// Set the new model on the view.
	ui->emailFolderListView->setModel(model);
	
	// TODO: connect 'clicked' signal from view.
	
	return true;
}


// -- PROCESS ACCOUNT ENTRIES ---
bool MainWindow::processAccountEntries(void* data, int argc, char* argv[], char* colNames[]) {
	// data		- Parent item (QStandardItem)
	// argc		- Number of arguments.
	// argv		- Arguments.
	// colNames	- Column names for the arguments.
	
	QStandardItem* parentItem = (QStandardItem*) data;
	
	// Open the account's 'mail.db' SQLite database and read the folders for that account.
	// Add each folder to the folder list model.
	
	// Open the SQLite database.
	// Read the folder id and name as well as the folded state. Add each folder to the 
}


// --- PROCESS MAIL ENTRIES ---
bool MainWindow::processMailEntries(void* data, int argc, char* argv[], char* colNames[]) {
	//
}


// --- SYNC EMAIL ---
// For all accounts, attempt to establish a connection to the remote server and synchronise emails.
void MainWindow::syncEmail() {
    //
}


// --- QUIT ---
void MainWindow::quit() {
    // TODO: clean-up, save window positions.
    
    exit(0);
}
