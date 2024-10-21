#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <iomanip>

using namespace std;

class Book {
private:
	long id;
	string name;
	string author;
	int year;
	int quantity;
public:
	Book() {
	}
	Book(
		long id,
		string name,
		string author,
		int year,
		int quantity) :
		id(id), name(name), author(author), year(year), quantity(quantity) {}
	void setId(long id) { this->id = id; }
	long getId() { return id; }
	void setName(string name) { this->name = name; }
	string getName() { return name; }
	void setAuthor(string author) { this->author = author; }
	string getAuthor() { return author; }
	void setYear(int year) { this->year = year; }
	int getYear() { return year; }
	void setQuantity(int quantity) { this->quantity += quantity; }
	int getQuantity() { return quantity; }
	void toString() {
		cout << setw(10) << id << setw(40) <<
			name << setw(30) <<
			author << setw(15) <<
			year << setw(10) <<
			quantity << '\n';
	}
};

class Reader {
private:
	string name;
	string phoneNumber;
	bool status;
public:
	Reader() {
	}
	Reader(
		string name,
		string phoneNumber) :
		name(name), phoneNumber(phoneNumber) {
		status = false;
	}
	Reader(
		string name,
		string phoneNumber,
		bool status) :
		name(name), phoneNumber(phoneNumber), status(status) {
	}
	void setName(string name) { this->name = name; }
	string getName() { return name; }
	void setPhoneNumber(string phoneNumber) {
		this->phoneNumber = phoneNumber;
	}
	string getPhoneNumber() {
		return phoneNumber;
	}
	void setStatus(bool status) { this->status = status; }
	bool getStatus() { return status; }
	void toString() {
		string readerStatus = "CHUA TAO THE";
		if (status == 1) readerStatus = "DA TAO THE";
		cout << setw(20) << name << setw(15) <<
			phoneNumber << setw(20) <<
			readerStatus << '\n';
	}
};

class ReadingCard {
private:
	string id;
	Reader reader;
	vector<Book> borrowedBooks;
	void setId(string id) {
		this->id = id;
	}
public:
	ReadingCard() {}
	ReadingCard(Reader reader) : reader(reader) {
		setId(reader.getPhoneNumber());
	}
	string getId() {
		return id;
	}
	void setReader(Reader reader) {
		this->reader = reader;
		setId(reader.getPhoneNumber());
	}
	Reader getReader() { return reader; }
	void setBorrowedBooks(Book book) {
		borrowedBooks.push_back(book);
	}
	vector<Book> getBorrowedBooks() {
		return borrowedBooks;
	}
	void returnBorrowedBook(long bookId) {
		for (auto a = borrowedBooks.begin(); a != borrowedBooks.end();) {
			Book book = *a;
			if (bookId == book.getId()) {
				borrowedBooks.erase(a);
				break;
			}
			else
				a++;
		}
	}
	void toString() {
		for (auto a = borrowedBooks.begin(); a != borrowedBooks.end(); a++) {
			Book book = *a;
			cout << setw(10) << book.getId() << setw(40) << book.getName() << setw(30) << book.getAuthor() << setw(15) << book.getYear() << endl;
		}
	}
};

class LibraryManagement {
private:
	vector<Book> books;
	vector<Reader> readers;
	vector<ReadingCard> readingCards;
public:
	LibraryManagement() {}
	LibraryManagement(
		vector<Book> books,
		vector<Reader> readers,
		vector<ReadingCard> readingCards
	) : books(books), readers(readers), readingCards(readingCards) {}
	void setBooks(vector<Book> books) {
		this->books = books;
	}
	void setBooks(Book book) { books.push_back(book); }
	vector<Book> getBooks() { return books; }
	void setReaders(vector<Reader> readers) { this->readers = readers; }
	void setReaders(Reader reader) { readers.push_back(reader); }
	vector<Reader> getReaders() { return readers; }
	void setReadingCards(vector<ReadingCard> readingCards) { this->readingCards = readingCards; }
	void setReadingCards(ReadingCard readingCard) { readingCards.push_back(readingCard); }
	vector<ReadingCard> getReadingCards() { return readingCards; }
};

class Menu {
private:
	LibraryManagement libraryManagement;
public:
	Menu() {
		vector<Book> books;
		vector<Reader> readers;
		vector<ReadingCard> readingCards;
		string bookName;
		string readerName;
		string author;
		int year;
		int quantity;
		int choose2;
		int readerId;
		long bookId;
		string sdt;
		bool check = false;
		bool check1 = false;
		bool check3 = false;
		bool check4 = false;
		readCSVFile("Book.csv");
		readCSVFile("Reader.csv");
		int choose;
		do {
			check = false;
			check1 = false;
			check3 = false;
			check4 = false;
			menu();
			cout << "Nhap lua chon cua ban: ";
			cin >> choose;
			switch (choose) {
			case 0:
				break;
			case 1:
				system("cls");
				books = libraryManagement.getBooks();
				cout << "-----------------------------------------DANH SACH SACH HIEN CO------------------------------------------" << endl;
				cout << setw(10) << "ID" << setw(40) << "TEN" << setw(30) << "TAC GIA" << setw(15) << "NAM PHAT HANH" << setw(10) << "SO LUONG" << endl;
				for (auto i = books.begin(); i != books.end(); i++) {
					Book book = *i;
					book.toString();
				}
				break;
			case 2:
				system("cls");
				readers = libraryManagement.getReaders();
				cout << "---------------------DANH SACH DOC GIA--------------------------" << endl;
				cout << setw(20) << "TEN" << setw(15) << "SDT" << setw(20) << "TRANG THAI THE" << endl;
				for (auto i = readers.begin(); i != readers.end(); i++) {
					Reader reader = *i;
					reader.toString();
				}
				break;
			case 3:
				system("cls");
				cout << "------------THEM SACH-------------" << endl;
				books = libraryManagement.getBooks();
				cout << "1. Them sach da ton tai." << endl;
				cout << "2. Them sach moi." << endl;
				cout << "Lua chon cua ban: ";
				cin >> choose2;
				switch (choose2) {
				case 1:
					cout << "Nhap ID sach muon them: ";
					cin >> bookId;
					for (int i = 0; i < books.size(); i++) {
						if (bookId == books[i].getId()) {
							check = !check;
							cout << "Nhap so luong sach: ";
							cin >> quantity;
							books[i].setQuantity(quantity);
							libraryManagement.setBooks(books);
							cout << "Them sach thanh cong." << endl;
						}
					}
					if (!check) cout << "Khong tim thay sach co ID tuong ung." << endl;
					break;
				case 2:
					cin.ignore();
					cout << "Nhap ten sach: ";
					getline(cin, bookName);
					cout << "Nhap ten tac gia: ";
					getline(cin, author);
					cout << "Nhap nam phat hanh: ";
					cin >> year;
					cout << "Nhap so luong sach: ";
					cin >> quantity;
				makeRandomNumber:
					bookId = getRandomNumber();
					for (auto i = books.begin(); i != books.end(); i++) {
						Book book = *i;
						if (bookId == book.getId()) goto makeRandomNumber;
					}
					libraryManagement.setBooks(Book(bookId, bookName, author, year, quantity));
					break;
				default:
					cout << "Nhap sai lua chon." << endl;
					break;
				}
				break;
			case 4:
				system("cls");
				cout << "------------XOA SACH--------------" << endl;
				books = libraryManagement.getBooks();
				cout << "Nhap ID cua sach can xoa: ";
				cin >> bookId;
				for (auto i = books.begin(); i != books.end(); ) {
					Book book = *i;
					if (bookId == book.getId()) {
						check = !check;
						books.erase(i);
						cout << "Xoa sach thanh cong." << endl;
						break;
					}
					else i++;
				}
				if (!check) cout << "Khong tim thay sach co ID tuong ung." << endl;
				libraryManagement.setBooks(books);
				break;
			case 5:
				system("cls");
				cout << "-------------------XOA DOC GIA-------------------" << endl;
				readers = libraryManagement.getReaders();
				cout << "Nhap SDT cua doc gia can xoa: ";
				cin >> sdt;
				for (auto i = readers.begin(); i != readers.end(); ) {
					Reader reader = *i;
					if (sdt == reader.getPhoneNumber()) {
						check = !check;
						readers.erase(i);
						cout << "Xoa doc gia thanh cong.";
						break;
					}
					else i++;
				}
				if (!check) cout << "Khong tim thay doc gia co SDT tuong ung." << endl;
				libraryManagement.setReaders(readers);
				break;
			case 6:
				system("cls");
				cout << "----------------LAM THE-------------------" << endl;
				readers = libraryManagement.getReaders();
				cout << "Nhap SDT cua doc gia can lam the: ";
				cin >> sdt;
				for (int i = 0; i < readers.size(); i++) {
					if (sdt == readers[i].getPhoneNumber()) {
						check = !check;
						if (readers[i].getStatus()) cout << "Doc gia nay da lam the." << endl;
						else {
							readers[i].setStatus(true);
							libraryManagement.setReaders(readers);
							libraryManagement.setReadingCards(ReadingCard(readers[i]));
							cout << "Lam the thanh cong." << endl;
						}
						break;
					}
				}
				if (!check) cout << "Khong tim thay doc gia co SDT tuong ung." << endl;
				break;
			case 7:
				system("cls");
				cout << "-------------MUON SACH-------------" << endl;
				books = libraryManagement.getBooks();
				readers = libraryManagement.getReaders();
				readingCards = libraryManagement.getReadingCards();
				cout << "Nhap SDT cua doc gia muon muon sach: ";
				cin >> sdt;
				for (int i = 0; i < readers.size(); i++) {
					if (sdt == readers[i].getPhoneNumber()) {
						check = !check;
						if (readers[i].getStatus()) {
							check3 = !check3;
							cout << "Nhap ID sach can muon: ";
							cin >> bookId;
							for (int j = 0; j < books.size(); j++) {
								if (bookId == books[j].getId()) {
									check1 = !check1;
									if (books[j].getQuantity() > 0) {
										for (int k = 0; k < readingCards.size(); k++) {
											if (sdt == readingCards[k].getId()) {
												vector<Book> borrowedBooks = readingCards[k].getBorrowedBooks();
												for (int l = 0; l < borrowedBooks.size(); l++) {
													if (bookId == borrowedBooks[l].getId()) {
														cout << "Sach nay da duoc doc gia muon." << endl;
														check4 = !check4;
													}
												}
												if (!check4) {
													readingCards[k].setBorrowedBooks(books[j]);
													libraryManagement.setReadingCards(readingCards);
													books[j].setQuantity(-1);
													libraryManagement.setBooks(books);
													cout << "Muon sach thanh cong." << endl;
												}
											}
										}
									}
									else cout << "Sach ban muon muon da het." << endl;
								}
							}
							if (!check1) cout << "Khong tim thay sach voi ID tuong ung." << endl;
							break;
						}
						if (!check3) cout << "Doc gia nay chua lam the." << endl;
					}
				}
				if (!check) cout << "Khong tim thay doc gia co SDT tuong ung." << endl;
				break;
			case 8:
				system("cls");
				cout << "-------------TRA SACH-------------" << endl;
				books = libraryManagement.getBooks();
				readers = libraryManagement.getReaders();
				readingCards = libraryManagement.getReadingCards();
				cout << "Nhap SDT cua doc gia muon tra sach: ";
				cin >> sdt;
				for (int i = 0; i < readers.size(); i++) {
					if (sdt == readers[i].getPhoneNumber()) {
						check = !check;
						if (readers[i].getStatus()) {
							check3 = !check3;
							cout << "Nhap ID sach can tra: ";
							cin >> bookId;
							for (int j = 0; j < books.size(); j++) {
								if (bookId == books[j].getId()) {
									check1 = !check1;
									for (int k = 0; k < readingCards.size(); k++) {
										if (sdt == readingCards[k].getId()) {
											vector<Book> borrowedBooks = readingCards[k].getBorrowedBooks();
											for (int l = 0; l < borrowedBooks.size(); l++) {
												if (bookId == borrowedBooks[l].getId()) check4 = !check4;
											}
											if (!check4) cout << "Sach nay chua duoc doc gia muon." << endl;
											else {
												readingCards[k].returnBorrowedBook(books[j].getId());
												libraryManagement.setReadingCards(readingCards);
												books[j].setQuantity(1);
												libraryManagement.setBooks(books);
												cout << "Tra sach thanh cong." << endl;
											}
										}
									}
								}
							}
							if (!check1) cout << "Khong tim thay sach voi ID tuong ung." << endl;
							break;
						}
						if (!check3) cout << "Doc gia nay chua lam the." << endl;
					}
				}
				if (!check) cout << "Khong tim thay doc gia co SDT tuong ung." << endl;
				break;
			case 9:
				system("cls");
				readers = libraryManagement.getReaders();
				readingCards = libraryManagement.getReadingCards();
				cout << "----------THONG TIN DOC GIA-------------" << endl;
				cout << "Nhap SDT cua doc gia muon tim kiem: ";
				cin >> sdt;
				for (int i = 0; i < readers.size(); i++) {
					if (sdt == readers[i].getPhoneNumber()) {
						check = !check;
						cout << setw(20) << "TEN" << setw(15) << "SDT" << setw(20) << "TRANG THAI THE" << endl;
						readers[i].toString();
						if (readers[i].getStatus()) {
							cout << "Danh sach sach da muon: " << endl;
							cout << setw(10) << "ID" << setw(40) << "TEN" << setw(30) << "TAC GIA" << setw(15) << "NAM PHAT HANH" << endl;
							for (int i = 0; i < readingCards.size(); i++) {
								if (sdt == readingCards[i].getId()) {
									readingCards[i].toString();
								}
							}
						}
					}
				}
				if (!check) cout << "Khong tim thay doc gia voi SDT tuong ung." << endl;
				break;
			case 10:
				system("cls");
				readers = libraryManagement.getReaders();
				cout << "-----------THEM DOC GIA-------------" << endl;
				cin.ignore();
				cout << "Nhap ten doc gia: ";
				getline(cin, readerName);
			getPhoneNumber:
				cout << "Nhap SDT cua doc gia: ";
				cin >> sdt;
				for (int i = 0; i < readers.size(); i++) {
					if (sdt == readers[i].getPhoneNumber()) {
						cout << "SDT nay da duoc tao." << endl;
						goto getPhoneNumber;
					}
				}
				libraryManagement.setReaders(Reader(readerName, sdt));
				break;
			default:
				system("cls");
				cout << "Nhap sai lua chon." << endl;
			}
			system("pause");
			system("cls");
		} while (choose != 0);
		writeCSVFile();
		cout << "Cam on da su dung dich vu cua thu vien.";
	}

	void menu() {
		cout << "--------QUAN LI THU VIEN-------" << endl;
		cout << "1. Hien danh sach sach hien co." << endl;
		cout << "2. Hien danh sach doc gia." << endl;
		cout << "3. Them sach." << endl;
		cout << "4. Xoa sach." << endl;
		cout << "5. Xoa doc gia." << endl;
		cout << "6. Lam the." << endl;
		cout << "7. Muon sach." << endl;
		cout << "8. Tra sach." << endl;
		cout << "9. Thong tin doc gia." << endl;
		cout << "10. Them doc gia." << endl;
		cout << "0. Thoat chuong trinh." << endl;
		cout << "--------------------------------" << endl;
	}
	bool stob(const std::string& str) {
		return (str == "1");
	}
	void readCSVFile(string fileName) {
		ifstream file(fileName);
		string line;

		if (!file) {
			cout << "Khong mo duoc file.\n";
			return;
		}

		while (getline(file, line)) {
			vector<string> tokens;
			stringstream ss(line);
			string token;
			while (getline(ss, token, ',')) {
				tokens.push_back(token);
			}
			if (tokens.size() == 5) {
				for (int i = 0; i < tokens[0].length(); ) {
					if (!isdigit(static_cast<unsigned char>(tokens[0][i]))) {
						tokens[0].erase(i, 1);
					}
					else {
						i++;
					}
				}
				long id = stol(tokens[0]);
				string name = tokens[1];
				string author = tokens[2];
				int year = stoi(tokens[3]);
				int quantity = stoi(tokens[4]);
				Book book = Book(id, name, author, year, quantity);
				libraryManagement.setBooks(book);
			}
			else {
				for (int i = 0; i < tokens[0].length(); ) {
					char check = tokens[0][i];
					if (!isalpha(static_cast<unsigned char>(check)) && !isblank(static_cast<unsigned char>(check))) {
						tokens[0].erase(i, 1);
					}
					else {
						i++;
					}
				}
				string name = tokens[0];
				string phoneNumber = tokens[1];
				bool status = stob(tokens[2]);
				Reader reader = Reader(name, phoneNumber, status);
				libraryManagement.setReaders(reader);
				if (status) {
					libraryManagement.setReadingCards(ReadingCard(reader));
					ifstream file1("Borrow.csv");
					string line1;
					if (!file1) {
						cout << "Khong mo duoc file.\n";
						return;
					}
					while (getline(file1, line1)) {
						vector<string> tokens1;
						stringstream ss1(line1);
						string token1;
						while (getline(ss1, token1, ',')) {
							tokens1.push_back(token1);
						}
						for (int i = 0; i < tokens1[0].length(); ) {
							if (!isdigit(static_cast<unsigned char>(tokens1[0][i]))) {
								tokens1[0].erase(i, 1);
							}
							else {
								i++;
							}
						}
						if (tokens1[0] == phoneNumber) {
							vector<ReadingCard> readingCards = libraryManagement.getReadingCards();
							readingCards.back().setBorrowedBooks(
								Book(
									stol(tokens1[1]),
									tokens1[2],
									tokens1[3],
									stoi(tokens1[4]),
									stoi(tokens1[5])
								));
							libraryManagement.setReadingCards(readingCards);
						}
					}
					file1.close();
				}
			}
		}
		file.close();
	}
	long getRandomNumber() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<long> dis(100000, 999999);
		return dis(gen);
	}
	void writeCSVFile() {
		ofstream outputFile("Book.csv");
		if (outputFile.is_open()) {
			for (auto& book : libraryManagement.getBooks()) {
				outputFile << book.getId() << "," <<
					book.getName() << "," <<
					book.getAuthor() << "," <<
					book.getYear() << "," <<
					book.getQuantity() << endl;
			}
			outputFile.close();
		}
		else {
			cout << "Khong the mo file." << endl;
		}
		ofstream outputFile1("Reader.csv");
		if (outputFile1.is_open()) {
			for (auto& reader : libraryManagement.getReaders()) {
				outputFile1 << reader.getName() << "," <<
					reader.getPhoneNumber() << "," <<
					reader.getStatus() << "," << endl;
			}
			outputFile1.close();
		}
		else {
			cout << "Khong the mo file." << endl;
		}
		ofstream outputFile2("Borrow.csv");
		if (outputFile2.is_open()) {
			for (auto& readingCard : libraryManagement.getReadingCards()) {
				for (auto& book : readingCard.getBorrowedBooks()) {
					outputFile2 <<
						readingCard.getReader().getPhoneNumber() << "," <<
						book.getId() << "," <<
						book.getName() << "," <<
						book.getAuthor() << "," <<
						book.getYear() << "," <<
						"1" << endl;
				}
			}
			outputFile2.close();
		}
		else {
			cout << "Khong the mo file." << endl;
		}
	}
};

int main() {
	Menu menu;
	return 0;
}