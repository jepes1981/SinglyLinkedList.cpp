#include <iostream>
//current issue - tail is getting messed up
class node
{
public:
    int data;
    node *next;
};

class list
{
    node *head;
    node *tail;

public:
    list()
    {
        head = NULL;
        tail = NULL;
        std::cout << "list contructor called" << std::endl;
        std::cout << "head is: " << head << std::endl;
        std::cout << "tail is: " << tail << std::endl;
    }
    ~list()
    {
        std::cout << "list deconstructor called" << std::endl;
        node *marker = new node;
        node *delhead = new node;
        marker = head;
        delhead = head;
        while (marker)
        {
            std::cout << "deleting " << delhead->data << std::endl;
            delete delhead;
            marker = marker->next;
            delhead = marker;
        }
        delete delhead;
        delete marker;
    }
    void addNode(int _data)
    {
        node *temp = new node;
        temp->data = _data;

        if (head == NULL)
        {
            head = temp;
            head->next = temp;
            tail = temp;
            tail->next = temp;
            temp->next = NULL;
        }
        else
        {
            temp->next = head;
            head = temp;
        }
    }

    void appendNode(int _data)
    {
        node *temp = new node;
        temp->data = _data;

        if (head == NULL)
        {
            head = temp;
            head->next = temp;
            tail = temp;
            tail->next = temp;
            temp->next = NULL;
        }
        else
        {
            tail->next = temp;
            temp->next = NULL;
            tail = temp;
        }
    }

    void insertNodeB(int _target, int _value) // insert _value before _target (only first instance)
    {
        //find _target
        node *midtracker = head;
        node *prev_marker = nullptr;

        if ((head == nullptr) && (tail == nullptr)) //there are no entries
        {
            std::cout << "there are no entries found. use addNode instead " << std::endl;
            return;
        }

        if (head->data == _target) // since _target is at start of list, will act like appendNode
        {
            addNode(_value);
            return;
        }
        prev_marker = midtracker;
        midtracker = midtracker->next; // move to next node since head is already evaluated
        while (midtracker)
        {
            if (midtracker->data == _target)
            {
                node *newnode = new node; //renamed temp to newnode for clarity
                newnode->data = _value;
                newnode->next = midtracker;
                prev_marker->next = newnode;
                return;
            }
            prev_marker = midtracker;
            midtracker = midtracker->next;
        }
        std::cout << "target value not found" << std::endl;
    }

    void insertNodeA(int _target, int _value) // insert _value after _target
    {
        node *marker = head;
        // node *temp = nullptr; // useless variable
        if ((head == nullptr) && (tail == nullptr)) //there are no entries
        {
            std::cout << "there are no entries found. use addNode instead " << std::endl;
            return;
        }
        while (marker)
        {
            if (marker->data == _target)
            {
                node *newnode = new node();
                newnode->data = _value;
                // temp = marker;                    // this was useless
                newnode->next = marker->next;
                // temp->next = newnode;                 // was useless, new code just below
                marker->next = newnode;
                if (marker == tail)
                {
                    tail = newnode;
                }
                return;
            }
            marker = marker->next;
        }
        std::cout << "target value not found for inserNodeA" << std::endl;
    }
    void listNode(void)
    {
        node *lister;
        lister = head;
        if (head)
        {

            std::cout << "head: " << head << " data: " << head->data << " head->next: " << head->next << std::endl;
            std::cout << "tail: " << tail << " data: " << tail->data << " tail->next: " << tail->next << std::endl
                      << std::endl;
        }
        else
        {
            std::cout << "no entry found." << std::endl;
        }
        while (lister)
        {
            std::cout << "addr: " << lister << " data: " << lister->data << " ->next: " << lister->next << std::endl;
            lister = lister->next;
        }
    }
    void deleteNode(int _target)
    {
        node *marker = head;
        node *previousNode = nullptr;
        if (head->data == _target) // if _target is found at head, move head to next node and delete previous head
        {
            marker = head;
            if (head == tail) //check if there is only 1 entry left
            {
                tail = nullptr; // then point it to nothing
            }
            head = head->next;
            delete marker;
            return;
        }
        previousNode = marker;
        marker = marker->next;
        while (marker)
        {
            if (marker->data == _target)
            {
                previousNode->next = marker->next;
                std::cout << "previousNode: " << previousNode << " data: " << previousNode->data << " ->next: " << previousNode->next << std::endl;
                std::cout << "marker: " << marker << " data: " << marker->data << " ->next: " << marker->next << std::endl;
                if (tail == marker)
                {
                    tail = previousNode;
                }
                delete marker;
                return;
            }
            previousNode = marker;
            marker = marker->next;
        }
        std::cout << "target value for deletion not found" << std::endl;
    }
    void sortNodeAscending(void)
    {
        node *marker = head;
        node *previousnode = nullptr;
        // node *temp = nullptr;
        bool switchMade = true;
        int SwitchCount = 0;
        if ((head->next == nullptr) || (head == nullptr)) // head has only one entry or no entry at all
        {
            //list only have 1 entry, return without doing nothing
            return;
        }
        else if (head->next->next == nullptr) //there are only 2 entries
        {
            if (head->data > head->next->data) // check if needed to switch
            {
                previousnode = marker;
                marker = marker->next;
                previousnode->next = marker->next;
                marker->next = previousnode;
                head = marker;
                tail = previousnode;
                return; // then return because there are only two entries.
            }
            else
                return; // since there are only two entries and already in asecending order.
        }

        // now if there are more than 2 entries.
        node *previousOfPrevious = nullptr;
        while (switchMade)
        {
            previousOfPrevious = previousnode;
            previousnode = marker;
            marker = marker->next;

            if (previousnode->data > marker->data) // if true, make the switch
            {
                if (previousnode == head) // check if previous node is the head. make sure to maintain head.
                {
                    previousnode->next = marker->next;
                    marker->next = previousnode;
                    head = marker; // this is the new head
                    SwitchCount++;
                }
                else
                {
                    if (marker == tail) // check if marker is the tail. make sure to maintain tail.
                    {
                        previousOfPrevious->next = marker;
                        previousnode->next = marker->next;
                        marker->next = previousnode;
                        tail = previousnode;
                        SwitchCount++;
                    }
                    else
                    {
                          previousOfPrevious->next = marker;
                        previousnode->next = marker->next;
                        marker->next = previousnode;
                        SwitchCount++;                      
                    }
                }
            }
            else
            {
                if (previousnode->data > marker->data)
                {
                    // normal switch
                    previousOfPrevious->next = marker;
                    previousnode->next = marker->next;
                    marker->next = previousnode;
                    SwitchCount++;
                }
            }
            if ((marker->next == nullptr) && (SwitchCount == 0)) // check if end of list and no switch made
            {
                return;
            }
            else // else reset marker and SwitchCount and loop again
            {
                if (marker->next == nullptr)
                {
                    marker = head;
                    SwitchCount = 0;
                }
            }
        }
    }
};

int main()
{
    list myList;
    int options{99}, target{0}, value{0};

    myList.appendNode(5);
    myList.appendNode(4);
    myList.appendNode(3);
    myList.appendNode(2);
    myList.appendNode(1);

    while (options)
    {
        myList.listNode();
        std::cout << "1. addNode" << std::endl;
        std::cout << "2. appendNode" << std::endl;
        std::cout << "3. inserNodeA" << std::endl;
        std::cout << "4. inserNodeB" << std::endl;
        std::cout << "5. deleteNode" << std::endl;
        std::cout << "6. listNode" << std::endl;
        std::cout << "7. sortNode" << std::endl;

        std::cout << "0. exit program" << std::endl;

        std::cout << "what do you want to do? ";
        std::cin >> options;
        switch (options)
        {
        case 1:
            std::cout << "enter value to start of list: ";
            std::cin >> value;
            myList.addNode(value);
            break;
        case 2:
            std::cout << "enter value to end of list: ";
            std::cin >> value;
            myList.appendNode(value);
            break;
        case 3:
            std::cout << "enter value of the target node: ";
            std::cin >> target;
            std::cout << "enter value to add after the target value: ";
            std::cin >> value;
            myList.insertNodeA(target, value);
            break;
        case 4:
            std::cout << "enter value of the target node: ";
            std::cin >> target;
            std::cout << "enter value to add before the target value: ";
            std::cin >> value;
            myList.insertNodeB(target, value);
            break;
        case 5:
            std::cout << "enter value of node to delete: ";
            std::cin >> target;
            myList.deleteNode(target);
            break;
        case 6:
            // myList.listNode();  //already listing prior showing options.
            break;
        case 7:
            myList.sortNodeAscending();
            break;
        case 0:
            return 0;
            break;
        default:
            std::cout << "option invalid, try again." << std::endl;
            // break;
        }
    }
    return 0;
}
