#ifndef MULTIWIN_H
#define MULTIWIN_H

#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QRadioButton>
#include <QListWidget>
#include <QTextEdit>

#include <string>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <iostream> // test
#include <cstdlib>

#include "../lib/webpage.h"
#include "../lib/searcheng.h"
#include "../lib/pageparser.h"
#include "../lib/mdpageparser.h"
#include "../lib/myset.h"
#include "../lib/comparator.h"
#include "lib/msort.h"
#include "lib/util.h"


class Multiwin : public QWidget
{
  Q_OBJECT
public:
  Multiwin(std::string index_file);
  ~Multiwin();
public slots:
  void searchButtonClicked();
  void exitButtonClicked();
  void quitButtonClicked();
  void singleWordRButtonClicked();
  void orRButtonClicked();
  void andRButtonClicked();
  void sortByPageRankButtonClicked();
  void sortByNameButtonClicked();
  void sortByIncomingButtonClicked();
  void sortByOutgoingButtonClicked();
  void filesnameListItemDblClicked(QListWidgetItem* filenameItem);
  void closeEvent(QCloseEvent *event);
  void sortNameButtonClicked();
  void sortIncomingButtonClicked();
  void sortOutgoingButtonClicked();
  std::string get_filename(std::string itemString);
  //void get_config_inputs(std::string config_file_str, std::map<std::string, std::string>& config_inputs);

private:

  std::map<std::string, std::string> config_inputs;

  QHBoxLayout* linkNumLabel;
  QLabel* filenameLabel;
  QPushButton* searchButton;
  QWidget* displayWin;
  QPushButton* exitButton;
  QLineEdit* searchWordsInput;

  QPushButton* quitButton;
  QLabel* searchInputLabel;
  QRadioButton* andRButton;

  QListWidget* filenamesList;
  QPushButton* sortByPageRankButton;
  QPushButton* sortByNameButton;
  QPushButton* sortByIncomingButton;
  QPushButton* sortByOutgoingButton;

  // List of file names in the list widget
  std::vector<std::string> fileNames;

  bool andRButtonIsClicked;
  bool orRButtonIsClicked;
  bool singleWordRButtonIsClicked;

  std::string myIndexFileName;
  SearchEng* searchEngine;
  PageParser* parser;

  //webpage display window*****
  QVBoxLayout* displayLayout;
  QHBoxLayout* linkLists;
  QTextEdit* webpageContentsText;
  QLabel* displayWinLabel;
  QListWidget* outgoingLinkList;
  QListWidget* incomingLinkList;
  QHBoxLayout* linksLabelLayout;
  QLabel* inLinksLabel;
  QLabel* outLinksLabel;

  QPushButton* sortNameButton;
  QPushButton* sortIncomingButton;
  QPushButton* sortOutgoingButton;

  std::vector<WebPage*> wpOutgoingLinks;
  std::vector<WebPage*> wpIncomingLinks;

  std::vector<std::string> get_words_to_search(std::string inputLine);
  void str_to_lower(std::string& word);
  char char_to_lower(char c);

};
#endif