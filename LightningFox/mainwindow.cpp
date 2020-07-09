#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <curl/curl.h>

#include <iostream>
#include <string>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    
    // Setup menu connections.
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit()));
    
    // Open SQLite database file.
	if (sqlite3_open("settings.db", settings) != SQLITE_OK) {
		std::cerr << "Error opening settings database." << std::endl;
		sqlite3_close(settings);
		return;
	}
	
	// If this is the first run, create the necessary tables in the database.
	std::string query = "CREATE TABLE IF NOT EXISTS accounts (id INTEGER PRIMARY KEY AUTOINCREMENT \
						, name TEXT NOT NULL, type INTEGER NOT NULL, server TEXT, smtp TEXT, \
						user TEXT, pass TEXT)";
	char* errmsg = 0;
	if (sqlite3_exec(settings, query, 0, 0, errmsg) != SQLITE_OK) {
		std::cerr << "SQL error: " << errmsg << std::endl;
		sqlite3_free(errmsg);
		sqlite3_close(settings);
		return;
	}
    
    // Read in account and folder information. Create sidebar view, restore last open folder and
    // email.
	// For each account, create a root item in the sidebar, then attach the account's folders to it.
	
    
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
