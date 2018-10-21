#include <iostream>
#include <string>

using namespace std;

template<class T>
class LinkedList
{

protected:
    class ListNode
    {
        T value;
        ListNode *next;

        ListNode(T _value, ListNode *_next = nullptr)
        {
            value = _value;
            next = _next;
        }

        friend class LinkedList;
    };
    ListNode *head;

public:
    LinkedList():head(nullptr){}
    LinkedList(LinkedList&);
    void operator=(LinkedList&);
    T &operator[](int) const;
    void add(T);
    void copy(LinkedList&);
    void destroy();
    void *currentNode(int) const;
    bool insert(int, T);
    void print();
    bool remove(T);
    void reverse();
    int size() const;
    void sort();
    ~LinkedList();
};

template<class T>
LinkedList<T>::LinkedList(LinkedList& node)
{
    head = nullptr;
    copy(node);
}

template<class T>
void LinkedList<T>::operator=(LinkedList& node)
{
    copy(node);
}

template<class T>
T &LinkedList<T>::operator[](int sub) const
{
    ListNode *node = (ListNode *)currentNode(sub);

    if(sub == 0)
    {
        return node->value;
    }

    return node->next->value;
}

template<class T>
void LinkedList<T>::add(T value)
{
    if(!head)
    {
        head = new ListNode(value);
    }
    else
    {
        ListNode *nodePtr = head;

        while(nodePtr->next)
        {
            nodePtr = nodePtr->next;
        }

        nodePtr->next = new ListNode(value);
    }
}

template<class T>
void LinkedList<T>::copy(LinkedList& node)
{
    if(head) destroy();

    ListNode *nodePtr = node.head;

    while(nodePtr)
    {
        add(nodePtr->value);
        nodePtr = nodePtr->next;
    }
}

template<class T>
void *LinkedList<T>::currentNode(int sub) const
{
    int m_size = size();
    if(sub < 0 || sub >= m_size)
        throw "Out of range";

    int count = 0;

    ListNode *nodePtr = head;
    ListNode *prevPtr = nullptr;

    if(sub == 0)
        return head;

    while(true)
    {

        if(count ==  sub)
            break;

        count++;

        prevPtr = nodePtr;
        nodePtr = nodePtr->next;
    }

    ListNode *temp = prevPtr;
    temp->next = nodePtr;
    return prevPtr;
}

template<class T>
void LinkedList<T>::destroy()
{
    ListNode *nodePtr = head;
    while(nodePtr)
    {
        ListNode *garbade = nodePtr;
        nodePtr = nodePtr->next;

        delete garbade;
    }
    head = nullptr;
}

template<class T>
bool LinkedList<T>::insert(int pos, T value)
{
    ListNode *node = (ListNode *)currentNode(pos);

    if(!node)
        return false;

    if(pos == 0)
    {
        ListNode *temp = new ListNode(value, node);
        head = temp;
    }
    else
    {
        ListNode  *prevPtr = node, *nodePtr = node->next;
        prevPtr->next = new ListNode(value, nodePtr);
    }
    return true;

}

template<class T>
void LinkedList<T>::print()
{
    ListNode *nodePtr = head;
    while(nodePtr)
    {
        cout << nodePtr->value << " ";
        nodePtr = nodePtr->next;
    }
    cout << endl;
}

template<class T>
bool LinkedList<T>::remove(T value)
{
    bool found = false;

    if(!head) return found;

    if(head->value == value)
    {
        ListNode *nodePtr = head;
        head = head->next;
        delete nodePtr;

        found = true;
    }
    else
    {
        ListNode *nodePtr = head,
        *prevPtr = nullptr;

        while(nodePtr && nodePtr->value != value)
        {
            prevPtr = nodePtr;
            nodePtr = nodePtr->next;
        }

        if(nodePtr)
        {
            prevPtr->next = nodePtr->next;
            delete nodePtr;

            found = true;
        }
    }

    return found;
}

template<class T>
void LinkedList<T>::reverse()
{
    if(!head) return;

    ListNode *nodePtr = head,
             *headPtr = nullptr;

    while(nodePtr)
    {
        ListNode *temp = nodePtr;
        nodePtr = nodePtr->next;

        temp->next = headPtr;
        headPtr = temp;
    }
    head = headPtr;
}

template<class T>
int LinkedList<T>::size() const
{
    int i = 0;
    ListNode *node = head;

    while(node)
    {
        i++;
        node = node->next;
    }

    return i;
}

template<class T>
void LinkedList<T>::sort()
{
    ListNode *nodePtr = head, *headPtr = nullptr;

    while(nodePtr)
    {
        ListNode *temp = nodePtr;
        nodePtr = nodePtr->next;

        if(!headPtr ||  temp->value <= headPtr->value)
        {
            temp->next = headPtr;
            headPtr = temp;
        }
        else
        {
            ListNode *currentNode = headPtr, *prevNode = nullptr;

            while(currentNode)
            {
                if(temp->value <= currentNode->value)
                    break;

                prevNode = currentNode;
                currentNode = currentNode->next;
            }

            temp->next = currentNode;
            prevNode->next = temp;
        }
    }

    head = headPtr;
}

template<class T>
LinkedList<T>::~LinkedList()
{
    destroy();
    cout << endl << "destructor called" << endl;
}

int main()
{
    LinkedList<int> list;

    list.add(1);
    list.add(3);
    list.add(5);
    list.add(2);
    list.add(1);
    list.add(2);
    list.add(200);

    LinkedList<int>list2(list);

    LinkedList<int>list3 = list2;


    cout << "list 1 SIZE: " << list.size() << endl;

    cout << "list1 " << endl;
    list.print();
    cout << endl;

    cout << "list1 after reverse" << endl;
    list.reverse();
    list.print();
    cout << endl;

    cout << "list1 after remove" << endl;
    list.remove(2);
    list.print();
    cout << endl;

    cout << "list1 after sort" << endl;
    list.sort();
    list.print();
    cout << endl;
    cout << endl;

    cout << "list2" << endl;
    list2.print();
    cout << endl;

    cout << "list2 after sort" << endl;
    list2.sort();
    list2.print();
    cout << endl;

    cout << "list2 after reverse" << endl;
    list2.reverse();
    list2.print();
    cout << endl;
    cout << endl;

    cout << "list3" << endl;
    list3.print();
    cout << endl;

    cout << "list3 after reverse" << endl;
    list3.reverse();
    list3.print();
    cout << endl;

    cout << "list3 after sort" << endl;
    list3.sort();
    list3.print();

    LinkedList<string> list4;
    list4.add("tunji");
    list4.add("dimeji");
    list4.add("bolaji");
    list4.add("debby");
    list4.add("daniel");

    list4.insert(4, "oladimillion");

    cout << "List4" <<endl;
    list4.print();
    cout<<endl;

    int index = 5;
    try
    {
        cout << "list4 index: " << list4[index] << " - value" << endl;
    }
    catch (const char *err)
    {
        cout << "ERROR: " << err << endl;
    }
    cout << endl;
    cout << endl;

    return(0);
}
