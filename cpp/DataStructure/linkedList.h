#ifndef DATASTRUCTURE_LINKEDLIST_H
#define DATASTRUCTURE_LINKEDLIST_H
// ��������ͷ�ļ�
#include "status.h"

// ʹ��ģ��
template<typename T = int>
// ������
class LinkedList {
private:
    // �������
    struct Node {
        // ֵ
        T value;
        // ָ����һ���ļ���ָ��
        Node *next;
        // ɾ��Ĭ�Ϲ��캯��
        Node() = delete;
        // ���幹�캯��
        Node(const T &value) : value(value), next(nullptr) {}
    };
    // ����ͷָ��
    Node *head = nullptr;
    // ������
    int length = 0;
    // �Ƿ�����˳�ʼ��
    bool initaled = false;
public:
    // ��ʼ������
    status InitaList() {
        // �Ѿ���ʼ�����ķ���ERROR
        if (initaled) {
            // ���������Ϣ
            std::cerr << "The list had been initalized.\n";
            return ERROR;
        }
        // ���ȳ�ʼ��Ϊ0
        length = 0;
        // ѯ���Ƿ���ļ���ʼ��
        std::cout << "initalize from file(y/n):";
        char ch;
        // ����ѡ��
        std::cin >> ch;
        if (ch == 'y') {
            getchar();
            // �õ��ļ���
            std::cout << "Please enter name of the file: ";
            std::string file_name;
            std::getline(std::cin, file_name);
            // ���ļ���
            std::fstream fin(file_name, std::ios_base::in);
            // �鿴���Ƿ�ɹ�
            if (fin.is_open()) {
                // ������������
                initaled = true;
                int cnt = 0;
                // �õ����ݸ���
                fin >> cnt;
                // ����ֲ�����
                T temp;
                for (int i = 0; i < cnt; ++i) {
                    // �������
                    fin >> temp;
                    // ���뵽�������
                    ListInsert(length + 1, temp);
                }
                // �ر��ļ���
                fin.close();
                std::cout << "Initalize from file successfully.\n";
            }
            else {
                // �����������
                std::cerr << "Open file failed.\n";
                return ERROR;
            }
        }

        initaled = true;
        return OK;
    }

    // ��������
    status DestroyList() {
        // ���δ��ʼ�����ش���
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }

        Node *temp = head;
        Node *pre;
        // ������������ռ�
        while (temp != nullptr) {
            pre = temp->next;
            delete temp;
            temp = pre;
        }
        // ͷָ����Ϊ��
        head = nullptr;
        // ��������
        length = 0;
        // ��ʼ����Ϊfalse
        initaled = false;
        return OK;
    }

    // �������
    status ClearList() {
        // δ��ʼ���������
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }
        // Ψһ������Ǵݻٺ�ĳ�ʼ��״̬Ϊtrue
        DestroyList();
        initaled = true;
        return OK;
    }

    // ����Ƿ�Ϊ�ձ�
    bool ListEmpty() const {
        // δ��ʼ����Ĭ���ǿձ�
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return true;
        }
        // �жϳ����Ƿ�Ϊ0
        return length == 0;
    }

    // �õ�������
    int ListLength() const {
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return -1;
        }
        // ���س���
        return length;
    }

    // ��ȡ�ض�λ�õ�Ԫ��
    status GetElem(const int &index, T &e) const {
        // δ��ʼ������
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }
        // �ж��±��Ƿ�Ϸ�
        if (index < 0 || index > length) {
            std::cerr << "Index out of bounds.\n";
            return ERROR;
        }
        // ����ֲ�����
        auto temp = head;
        // index��Ԫ������ƶ�index-1�μ���
        for (int i = 0; i < index - 1; ++i) {
            temp = temp->next;
        }
        // ��ȡֵ
        e = temp->value;

        return OK;
    }

    // ��λԪ��
    status LocateElem(const T &e, int &index, Compare<T> comp) const {
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }
        // �ֲ�ͷָ��
        auto temp_ptr = head;
        // ����Ԫ�أ����Ƿ���compΪ���
        for (int i = 0; i < length; i++) {
            if (comp(e, temp_ptr->value)) {
                // ���ھͷ����±�
                index = i + 1;
                return OK;
            }
            // ָ�����
            temp_ptr = temp_ptr->next;
        }
        // �������û��
        index = 0;
        return ERROR;
    }

    // ��ȡǰ��Ԫ��
    status PriorElem(const T &cur, T &pre_e, Compare<T> comp) const {
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }
        // �ֲ�ͷָ��
        auto temp_ptr = head;
        // ����Ԫ��
        while (temp_ptr != nullptr && temp_ptr->next != nullptr) {
            // ����˴�Ԫ�صĺ����Ǹ�����Ԫ�أ����ش�Ԫ��
            if (comp(temp_ptr->next->value, cur)) {
                pre_e = temp_ptr->value;
                return OK;
            }
            temp_ptr = temp_ptr->next;
        }

        return ERROR;
    }

    // ��ú���
    status NextElem(const T &cur, T &next, Compare<T> comp) const {
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }
        auto temp_ptr = head;
        // �����Ԫ������compΪ�棬��һ����Ϊ����Ԫ��
        while (temp_ptr != nullptr && temp_ptr->next != nullptr) {
            if (comp(temp_ptr->value, cur)) {
                next = temp_ptr->next->value;
                return OK;
            }
            temp_ptr = temp_ptr->next;
        }

        return ERROR;
    }

    // ����Ԫ��
    status ListInsert(const int &index, const T &e) {
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }
        // �ж��±��Ƿ�Ϸ�
        if (index < 1 || index > length + 1) {
            std::cerr << "Index out of bounds\n";
            return ERROR;
        }
        // ʹ�ó�ʼֵ�½����
        auto t = new Node(e);
        // ���뵽��Ԫ��λ�����⴦��
        if (index == 1) {
            t->next = head;
            head = t;
        }
        else {
            // ����ƶ����ʵ�λ��
            auto pre = head;
            for (int i = 0; i < index - 2; ++i) {
                pre = pre->next;
            }
            // ��t����
            t->next = pre->next;
            pre->next = t;
        }
        // ���ȼ�1
        ++length;

        return OK;
    }

    // ɾ��Ԫ��
    status ListDelete(const int &index, T &e) {
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }
        // �ж��±�Ϸ���
        if (index < 1 || index > length) {
            std::cerr << "Index out of bounds\n";
            return ERROR;
        }

        // ɾ����Ԫ�����⴦��
        if (index == 1) {
            Node *temp = head;
            head = head->next;
            e = temp->value;
            delete temp;
        }
        else {
            auto pre = head;
            // �����ʵ�λ�ã��ҵ�Ҫɾ��Ԫ�ص�ǰ��
            for (int i = 0; i < index - 2; ++i) {
                pre = pre->next;
            }
            // ɾ��Ԫ��
            auto to_del = pre->next;
            pre->next = to_del->next;
            e = to_del->value;
            delete to_del;
        }
        // ���ȼ� 1
        --length;

        return OK;
    }

    // ����Ԫ��
    status ListTraverse(Visit<T> visit) {
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }
        // ֱ�ӱ�������
        auto temp_ptr = head;
        for (int i = 0; i < length; ++i) {
            // ʹ��visitָ��
            visit(temp_ptr->value);
            // ָ�����
            temp_ptr = temp_ptr->next;
        }

        return OK;
    }

    // �������浽�ļ���
    status ListSave() {
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }
        getchar();
        // �õ��ļ���
        std::cout << "Please enter the file name: ";
        std::string file_name;
        std::cin >> file_name;
        // ������ļ���
        std::fstream fout(file_name, std::ios_base::out);
        // ��д��Ԫ�ظ���
        fout << length << "\n";
        // ����д��
        auto temp_ptr = head;
        for (int i = 0; i < length; ++i) {
            fout << temp_ptr->value << "\n";
            temp_ptr = temp_ptr->next;
        }
        // �ر��ļ��������ļ�
        fout.close();
        return OK;
    }

    // ��������
    ~LinkedList() {
        // ��Ҫ�����ͷſռ���
        auto temp = head;
        while (temp != nullptr) {
            auto next = temp->next;
            delete temp;
            temp = next;
        }
        head = nullptr;
    }
};
#endif //DATASTRUCTURE_LINKEDLIST_H
