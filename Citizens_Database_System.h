#ifndef K_19I1708_H_
#define K_19I1708_H_

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

template<class T>
struct Queue
{
    T data;
    Queue *next;

    Queue(T v = 0)
    {
        data = v;
        next = NULL;
    }
};

template <class T>
class DataPipeline 
{
    private:
        Queue <T>*Front;
        Queue <T>*rear;

    public:
	    DataPipeline() 
        {
            Front = NULL;
            rear = NULL;
        }

        void enqueue(T value) 
        {
            Queue <T>*newQueue = new Queue<T>(value);

            if(is_empty())
            {
                Front = newQueue;
                rear = newQueue;
            }else{
                rear->next = newQueue;
                rear = newQueue;
            }
        } 

	    T dequeue() 
        {
            if(is_empty()) 
            {
                return 0; 
            }
            Queue <T>*temp = Front;
            T tmp = Front->data;
            Front = Front->next;
            delete temp;
            if(Front == NULL)
            {
                rear = NULL; 
            }
            return tmp;
	    }

	    T front() 
        {
            T tmp = Front->data;
		    return T(tmp);
	    }

	    T back() 
        {
		    return T(rear->data);
	    }

        void print()
        {
            if(is_empty())
            {
                cout<<"List is Empty!"<<endl;
            }else{
                Queue <T>*temp = Front;
                while(temp!=NULL)
                {
                    cout<<temp->data<<" ";
                    temp = temp->next;
                }
                cout<<endl;
            }
        }

        void read_file(string name)
        {
            ifstream file;
	        file.open(name, ios::in);
            string word = "";
            while(file>>word)
            {
                enqueue(word);
            }
        }

        bool is_empty() 
        {
		    return (Front == NULL);
	    }

        ~DataPipeline()
        {
            delete Front;
            delete rear;
        }
};

template<class T>
struct Node
{
    T data;
    Node <T>*next;

    Node(T n=0)
    {
        data = n;
        next = NULL;
    }
};

template<class T>
class AD
{
    private:
        Node <T>*stack;

    public:
        AD()
        {
            stack = NULL;
        }

        void push_roll(T value)
        {
            Node <T>*node = new Node <T>(value);
            if(is_empty())
            {
                stack = node;
            }else{
                Node <T>*tmp = stack;
                while(tmp->next != NULL)
                {
                    tmp = tmp->next;
                }
                tmp->next = node;
            }
        }

        bool is_empty() 
        {
            if(stack==NULL)
            {
                return true;
            }
            return false;
	    }

        void print()
        {
            cout<<"Printing AD Database :- ";
            Node <T>*tmp = stack;
            while(tmp != NULL)
            {
                cout<<tmp->data<<" ";
                tmp = tmp->next;
            }
            cout<<endl;
        }

        T top() 
        {
            T no = 0;
            Node <T>*tmp = stack;
            while(tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            no = tmp->data;
            return no;
	    }

        T pop() 
        {
            if(stack->next==NULL)
            {
                stack = NULL;
                return 0;
            }
            Node <T>*tmp = stack;
            while(tmp->next->next != NULL)
            {
                tmp = tmp->next;
            }
            delete tmp->next->next;
            tmp->next = NULL;
            return tmp->data;
	    }

        bool search(T val)
        {
            Node <T>*tmp = stack;
            while(tmp!=NULL)
            {   
                if(tmp->data==val)
                {
                    return true; 
                }
                tmp = tmp->next;
            }
            return false;
        }

        void empty() 
        {
            while(!is_empty())
            {
                pop();
            }
	    }

        ~AD()
        {
            delete stack;
        }
};

template <class T>
struct CBID_NODE;

template <class T>
struct CCID_NODE
{
    int CNIC;
    T Fine;
    T Charges;
    T Punishment;
    T Details_of_Crime;
    CBID_NODE <T>* criminal_data;
    CCID_NODE <T>*next;
    CCID_NODE *previous;
};

template <class T>
struct CCND_NODE 
{
    int CNIC;
    T Number;
    T Network;
    T Activation_Date;
    T Deactivation_Date;
    T Status;
    CBID_NODE <T>*user_data;
	CCND_NODE *next;
    CCND_NODE *previous;
};

template <class T>
struct CBID_NODE
{
    int CNIC;
    T Name;
    T Father_Name;
    T Gender;
    T Address;
    T Nationality;
    CCID_NODE <T>*crime;
    CCND_NODE <T>*network;
	CBID_NODE <T>*next;
    CBID_NODE <T>*previous;
};

template<class T>
class Database 
{
    private:
        AD <int>alien;
        CBID_NODE <T>*CBID;
        CCID_NODE <T>*CCID;
        CCND_NODE <T>*CCND;
        DataPipeline <T>dataPipeline;
    
    public:
	    Database(T filename , T filename1, T filename2) 
        {
            dataPipeline.read_file(filename); // Function in DataPipeline to read file
            CBID = NULL;
            while(!dataPipeline.is_empty())
            {
                CBID_NODE <T>*node = new CBID_NODE <T>();
                node->CNIC = stoi(dataPipeline.dequeue());
                node->Name = dataPipeline.dequeue();
                node->Father_Name = dataPipeline.dequeue();
                node->Gender = dataPipeline.dequeue();
                node->Address = dataPipeline.dequeue()+" ";
                node->Address += dataPipeline.dequeue()+" ";
                node->Address += dataPipeline.dequeue();
                node->Nationality = dataPipeline.dequeue();
                node->next = NULL;
                node->previous = NULL;
                node->crime = NULL;
                node->network = NULL;

                if(CBID==NULL)
                {
                    CBID = node;
                }else{
                    CBID_NODE <T>*tmp = CBID;
                    while(tmp->next!=NULL)
                    {
                        tmp = tmp->next;
                    }
                    tmp->next = node;
                    node->previous = tmp;
                }
            }

            dataPipeline.read_file(filename1);
            CCID = NULL;
            while(!dataPipeline.is_empty())
            {
                CCID_NODE <T>*node = new CCID_NODE<T>();
                node->CNIC = stoi(dataPipeline.dequeue());
                node->Charges = dataPipeline.dequeue();

                if(dataPipeline.front()=="life")
                {
                    node->Punishment = dataPipeline.dequeue()+" ";
                    node->Punishment += dataPipeline.dequeue()+" ";
                    node->Punishment += dataPipeline.dequeue();
                }else{
                    node->Punishment = dataPipeline.dequeue()+" ";
                    node->Punishment += dataPipeline.dequeue()+" ";
                    node->Punishment += dataPipeline.dequeue()+" ";
                    node->Punishment += dataPipeline.dequeue();
                }
                node->Fine = dataPipeline.dequeue();
                node->next = NULL;
                node->previous = NULL;
                node->criminal_data = NULL;

                CBID_NODE <T>*tmp_node = CBID;
                while(tmp_node != NULL)
                {
                    if(tmp_node->CNIC==node->CNIC)
                    {
                        tmp_node->crime = node;
                        node->criminal_data = tmp_node;
                        break;
                    }
                    tmp_node = tmp_node->next;
                }

                if(CCID==NULL)
                {
                    CCID = node;
                }else{
                    CCID_NODE <T>*tmp = CCID;
                    while(tmp->next!=NULL)
                    {
                        tmp = tmp->next;
                    }
                    tmp->next = node;
                    node->previous = tmp;
                }
            }

            dataPipeline.read_file(filename2);
            CCND = NULL;
            while(!dataPipeline.is_empty())
            {
                CCND_NODE <T>*node = new CCND_NODE <T>();
                node->CNIC = stoi(dataPipeline.dequeue());
                node->Number = dataPipeline.dequeue();
                node->Network = dataPipeline.dequeue();
                node->Activation_Date = dataPipeline.dequeue();
                node->Deactivation_Date = dataPipeline.dequeue();
                node->Status = dataPipeline.dequeue();
                node->next = NULL;
                node->previous = NULL;
                node->user_data = NULL;

                CBID_NODE <T>*tmp_node = CBID;
                while(tmp_node != NULL)
                {
                    if(tmp_node->CNIC==node->CNIC)
                    {
                        tmp_node->network = node;
                        node->user_data = tmp_node;
                        break;
                    }
                    tmp_node = tmp_node->next;
                }

                if(CCND==NULL)
                {
                    CCND = node;
                }else{
                    CCND_NODE <T>*tmp = CCND;
                    while(tmp->next!=NULL)
                    {
                        tmp = tmp->next;
                    }
                    tmp->next = node;
                    node->previous = tmp;
                }
            }
	    }

        T CBID_Search_by_CNIC(int cnic) 
        {
            CBID_NODE <T>*node = CBID;
            T tmp;
            while(node->CNIC!=cnic && node!=NULL)
            {
                node = node->next;
            }
            tmp = node->Name+" "+node->Father_Name+" "+node->Gender+" "+node->Address+" "+node->Nationality+
                +" "+node->crime->Charges+" "+node->crime->Punishment+" "+node->crime->Fine+
                " "+node->network->Number+" "+node->network->Network+" "+node->network->Activation_Date+" "+node->network->Deactivation_Date+
                " "+node->network->Status;
            return tmp; 
	    }

        T CCID_Search_by_CNIC(int cnic) 
        {
            T tmp = "";
            CCID_NODE <T>*node = CCID;
            while(node->CNIC!=cnic && node!=NULL)
            {
                node = node->next;
            }
            tmp = node->criminal_data->Name+" "+node->criminal_data->Father_Name+" "+node->criminal_data->Gender+" "+
                node->criminal_data->Address+" "+node->criminal_data->Nationality+" "+node->Charges+" "+node->Punishment+
                " "+node->Fine+" "+node->criminal_data->network->Number+" "+node->criminal_data->network->Network+" "+
                node->criminal_data->network->Activation_Date+" "+node->criminal_data->network->Deactivation_Date+
                " "+node->criminal_data->network->Status;
            return tmp; 
	    }

        T CCND_Search_by_CNIC(int cnic) 
        {
            T tmp = "";
            CCND_NODE <T>*node = CCND;
            while(node->CNIC!=cnic && node!=NULL)
            {
                node = node->next;
            }
            tmp = node->user_data->Name+" "+node->user_data->Father_Name+" "+node->user_data->Gender+" "+
                node->user_data->Address+" "+node->user_data->Nationality+" "+node->Number+" "+node->Network+" "+
                node->Activation_Date+" "+node->Deactivation_Date+" "+node->Status;
            return tmp; 
	    }

        bool updateCBIDName(T name, int cnic) 
        {
            CBID_NODE <T>*node = CBID;
            bool found = false;
            while(!found && node!=NULL)
            {
                if(node->CNIC==cnic)
                {
                    found = true;
                    node->Name = name;
                }
                node = node->next;
            }
            return found;
	    }

        bool updateCBIDFName(T F_Name, int cnic) 
        {
            CBID_NODE <T>*node = CBID;
            bool found = false;
            while(!found && node!=NULL)
            {
                if(node->CNIC==cnic)
                {
                    node->Father_Name = F_Name;
                    found = true;
                }
                node = node->next;
            }
            return found;
	    }

        bool updateCBIDAddress(T address, int cnic) 
        {
            CBID_NODE <T>*node = CBID;
            bool found = false;
            while(!found && node!=NULL)
            {
                if(node->CNIC==cnic)
                {
                    node->Address = address;
                    found = true;
                }
                node = node->next;
            }
            return found;
	    }

        bool updateCBIDNationality(T nationality, int cnic) 
        {
            CBID_NODE <T>*node = CBID;
            bool found = false;
            while(!found && node!=NULL)
            {
                if(node->CNIC==cnic)
                {
                    node->Nationality = nationality;
                    found = true;
                }
                node = node->next;
            }
            return found;
	    }

        bool addCrime(int cnic, T charges, T punishment, T fine)
        {
            CCID_NODE <T>*node = new CCID_NODE<T>();
            node->CNIC = cnic;
            node->Charges = charges;
            node->Punishment = punishment;
            node->Fine = fine;
            node->next = NULL;
            node->previous = NULL;

            bool found = false;
            if(CCID==NULL)
            {
                CCID = node;
            }else{
                CCID_NODE <T>*tmp = CCID;
                while(tmp->next!=NULL)
                {
                    tmp = tmp->next;
                }
                tmp->next = node;
                node->previous = tmp;
            }

            CBID_NODE <T>*tmp = CBID;
            while(!found && tmp!=NULL)
            {
                if(tmp->CNIC==cnic)
                {
                    tmp->crime = node;
                    found = true;
                }
                tmp = tmp->next;
            }
            return found;
        }
        
        bool updateCrime(int cnic, T charges, T punishment, T fine) 
        {
		    CCID_NODE <T>*node = CCID;
            bool found = false;
            while(!found && node!=NULL)
            {
                if(node->CNIC==cnic)
                {
                    found = true;
                    node->Charges = charges;
                    node->Punishment = punishment;
                    node->Fine = fine;
                }
                node = node->next;
            }
            return found;
	    }

        bool deleteCrime(int cnic, T charges, T punishment, T fine) 
        {
            bool found = false;
            CBID_NODE <T>*tmp = CBID;
            while(!found && tmp!=NULL)
            {
                if(tmp->CNIC==cnic)
                {
                    if(tmp->crime!=NULL)
                    {
                        tmp->crime = NULL;
                        found = true;
                    }
                }
                tmp = tmp->next;
            }
            return found;
        }

        int addNumber(int cnic, int number) 
        {
		    int no = 0;
            CCND_NODE <T>*node = new CCND_NODE <T>();
            node->CNIC = cnic;
            node->Number = to_string(number);
            node->next = NULL;
            node->previous = NULL;
            if(CCND==NULL)
            {
                CCND = node;
            }else{
                CCND_NODE <T>*tmp = CCND;
                while(tmp->next!=NULL)
                {
                    if(tmp->CNIC==cnic)
                    {
                        no++;
                    }
                    tmp = tmp->next;
                }
                tmp->next = node;
                no++;
                node->previous = tmp;
            }
            CBID_NODE <T>*tmp = CBID;
            while(tmp!=NULL)
            {
                if(tmp->CNIC==cnic)
                {
                    tmp->network->next = node;
                }
                tmp = tmp->next;
            }
            return no;
	    }

        int checkRegistred_No(int cnic)
        {
            int no = 0;
            CCND_NODE <T>*tmp = CCND;
            while(tmp->next!=NULL)
            {
                if(tmp->CNIC==cnic)
                {
                    if(tmp->Status=="active")
                    {
                        no++;
                    }
                }
                tmp = tmp->next;
            }    
            return no; 
        }

        CCND_NODE<T> swap(int cnic, int cnic1, T number, T number1)
        {
            CCND_NODE <T>*tmp = CCND;
            while(tmp->next!=NULL)
            {
                if(tmp->CNIC==cnic)
                {
                    tmp->Number = number1;
                }else if(tmp->CNIC==cnic1)
                {
                    tmp->Number = number;
                }
                tmp = tmp->next;
            }  
            return CCND;
        }
    
        AD<int>& declareAlien(int cnic)
        {
            CBID_NODE <T>*node = CBID;
            while(node!=NULL)
            {
                if(node->CNIC==cnic)
                {
                    node->Nationality=="Alien";
                    int no = node->CNIC;
                    alien.push_roll(no);
                    return alien;
                }
                node = node->next;
            }
            return alien;
	    }

        bool verifyAlienDBUpdate(int cnic)
        {
            return alien.search(cnic);
	    }

        void Display_AD()
        {
            alien.print();
        }

        int printcount()
        {
            int total = 0;
            CCND_NODE <T>*node = CCND;
            while(node!=NULL)
            {
                total++;
                node = node->next;
            }
            return total;
        }

        ~Database() 
        {
            delete CBID;
            delete CCID;
            delete CCND;
	    }
};

#endif