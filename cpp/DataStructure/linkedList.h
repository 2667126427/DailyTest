#ifndef DATASTRUCTURE_LINKEDLIST_H
#define DATASTRUCTURE_LINKEDLIST_H
#define LEN 100

#include "status.h"

	template<typename T = int>
	class LinkedList {
	private:
		struct Node {
			T value;
			Node *next;

			Node() = delete;

			explicit Node(const T &value) : value(value), next(nullptr) {}
		};

		Node *head = nullptr;
		int length = 0;
		bool initaled = false;
		using status = int;
	public:
		status InitaList(){
			if (initaled) {
				std::cerr << "The list had been initalized.\n";
				return ERROR;
			}

			length = 0;
			std::cout << "initalize from file(y/n):";
			char ch;
			std::cin >> ch;
			if (ch == 'y') {
				getchar();
				std::cout << "Please enter name of the file: ";
				std::string file_name;
				std::getline(std::cin, file_name);
				std::fstream fin(file_name, std::ios_base::in);
				if (fin.is_open()) {
					initaled = true;
					int cnt = 0;
					fin >> cnt;
					T temp;
					for (int i = 0; i < cnt; ++i) {
						fin >> temp;
						ListInsert(length + 1, temp);
					}
					fin.close();
					std::cout << "Initalize from file successfully.\n";
				}
				else {
					std::cerr << "Open file failed.\n";
					return ERROR;
				}
			}

			initaled = true;
			return OK;
		}

		status DestroyList() {
			if (!initaled) {
				std::cerr << "List is not initialized.\n";
				return ERROR;
			}

			Node *temp = head;
			Node *pre;
			while (temp != nullptr) {
				pre = temp->next;
				delete temp;
				temp = pre;
			}
			head = nullptr;
			length = 0;
			initaled = false;
			return OK;
		}

		status ClearList() {
			if (!initaled) {
				std::cerr << "List is not initialized.\n";
				return ERROR;
			}
			DestroyList();
			initaled = true;
			return OK;
		}

		bool ListEmpty() {
			if (!initaled) {
				std::cerr << "List is not initialized.\n";
				return true;
			}

			return length == 0;
		}

		int ListLength()  {
			if (!initaled) {
				std::cerr << "List is not initialized.\n";
				return -1;
			}

			return length;
		}

		status GetElem(const int &index, T &e) {
			if (!initaled) {
				std::cerr << "List is not initialized.\n";
				return ERROR;
			}
			if (index < 0 || index > length) {
				std::cerr << "Index out of bounds.\n";
				return ERROR;
			}
			auto temp = head;
			for (int i = 0; i < index - 1; ++i) {
				temp = temp->next;
			}
			e = temp->value;

			return OK;
		}

		status LocateElem(const T &e, int &index, Compare<T> comp) {
			if (!initaled) {
				std::cerr << "List is not initialized.\n";
				return ERROR;
			}
			auto temp_ptr = head;
			for (int i = 0; i < length; i++) {
				if (comp(e, temp_ptr->value)) {
					index = i + 1;
					return OK;
				}
				temp_ptr = temp_ptr->next;
			}
			index = 0;
			return ERROR;
		}

		status PriorElem(const T &cur, T &pre_e, Compare<T> comp) {
			if (!initaled) {
				std::cerr << "List is not initialized.\n";
				return ERROR;
			}
			auto temp_ptr = head;
			while (temp_ptr != nullptr && temp_ptr->next != nullptr) {
				if (comp(temp_ptr->next->value, cur)) {
					pre_e = temp_ptr->value;
					return OK;
				}
			}

			return OK;
		}

		status NextElem(const T &cur, T &next, Compare<T> comp) {
			if (!initaled) {
				std::cerr << "List is not initialized.\n";
				return ERROR;
			}
			auto temp_ptr = head;
			while (temp_ptr != nullptr && temp_ptr->next != nullptr) {
				if (comp(temp_ptr->value, cur)) {
					next = temp_ptr->next->value;
					return OK;
				}
			}

			return OK;
		}

		status ListInsert(const int &index, const T &e) {
			if (!initaled) {
				std::cerr << "List is not initialized.\n";
				return ERROR;
			}
			if (index < 1 || index > length + 1) {
				std::cerr << "Index out of bounds\n";
				return ERROR;
			}
			auto t = new Node(e);
			if (index == 1) {
				t->next = head;
				head = t;
			}
			else {
				auto pre = head;
				for (int i = 0; i < index - 2; ++i) {
					pre = pre->next;
				}
				t->next = pre->next;
				pre->next = t;
			}
			++length;

			return OK;
		}

		status ListDelete(const int &index, T &e) {
			if (!initaled) {
				std::cerr << "List is not initialized.\n";
				return ERROR;
			}
			if (index < 1 || index > length) {
				std::cerr << "Index out of bounds\n";
				return ERROR;
			}

			if (index == 1) {
				Node *temp = head;
				head = head->next;
				e = temp->value;
				delete temp;
			}
			else {
				auto pre = head;
				// 1 2 3
				for (int i = 0; i < index - 2; ++i) {
					pre = pre->next;
				}

				auto to_del = pre->next;
				pre->next = to_del->next;
				e = to_del->value;
				delete to_del;
			}
			--length;

			return OK;
		}

		status ListTraverse(Visit<T> visit) {
			if (!initaled) {
				std::cerr << "List is not initialized.\n";
				return ERROR;
			}

			auto temp_ptr = head;
			for (int i = 0; i < length; ++i) {
				visit(temp_ptr->value);
				temp_ptr = temp_ptr->next;
			}

			return OK;
		}

		status ListSave() {
			if (!initaled) {
				std::cerr << "List is not initialized.\n";
				return ERROR;
			}
			getchar();
			std::cout << "Please enter the file name: ";
			std::string file_name;
			std::cin >> file_name;
			std::fstream fout;
			fout.open(file_name, std::ios_base::out);
			fout << length << "\n";
			auto temp_ptr = head;
			for (int i = 0; i < length; ++i) {
				fout << temp_ptr->value << "\n";
				temp_ptr = temp_ptr->next;
			}
			fout.close();
			return OK;
		}

		~LinkedList() {
			auto temp = head;
			while (temp != nullptr) {
				auto next = temp->next;
				delete temp;
				temp = next;
			}
			head = nullptr;
		}
	};
//}


#endif //DATASTRUCTURE_LINKEDLIST_H
