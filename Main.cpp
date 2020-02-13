/****************************************************************/
/*                   Driver File                                */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
#include <iostream>
#include <fstream>

using namespace std;

void displayMenu();  

int main(int argc, char* argv[])
{
    // Object representing our network of cities.
    // (Linked list representation is in CountryNetwork)
    CountryNetwork CountryNet;
    string countryName, message;

    int choice = 0;
    string choice_str;
    while (choice != 5)
    {
        displayMenu();
        getline(cin, choice_str);
        choice = atoi(choice_str.c_str());
        // printf("choice is: %d", choice);
        // Object representing our network of cities.
        // (Linked list representation is in CountryNetwork)
        if(choice == 1)
        {
            CountryNet.loadDefaultSetup();
            CountryNet.printPath();
        }
        else if (choice == 2)
        {
            CountryNet.printPath();
        }
        else if (choice ==3)
        {   
            cout << "Enter name of the country to receive the message:" << endl;
            getline(cin, countryName);
            //cout << "--------------- " << endl;
            //cout << "country name is: " << countryName << endl;
            //cout << "--------------- " << endl;
            cout << "Enter the message to send:"<< endl;
            getline(cin, message);
            //cout << "--------------- " << endl;
            //cout << "message is: " << message;
            //cout << "--------------- " << endl;

            cout <<'\n';

            Country *ptrCountry = CountryNet.searchNetwork(countryName);

            //{
                CountryNet.transmitMsg(countryName, message);
            //}

        }
        else if (choice == 4)
        {   
            bool valid = false;
            string newCountry, previous;
            
            cout << "Enter a new country name:" << endl;
            
            getline(cin, newCountry);
            newCountry[0] = toupper(newCountry[0]);
            
            cout << "Enter the previous country name (or First):" << endl;


            while (valid == false)
            {
                
            
                getline(cin, previous);
                previous[0] = toupper(previous[0]);
                
                Country *ptrCountry = CountryNet.searchNetwork(previous);
                if (ptrCountry != NULL && previous != "First")
                {
                    CountryNet.insertCountry(ptrCountry, newCountry);
                    CountryNet.printPath();
                    valid = true;
                }
                else if (previous == "First")
                {
                    CountryNet.insertCountry(NULL, newCountry);
                    CountryNet.printPath();
                    valid = true;
                }
                else
                {
                    cout << "INVALID(previous country name)...Please enter a VALID previous country name!" << endl;
                }
            }
        }
    }
    cout << "Quitting..." << endl;
    cout << "Goodbye!"<< endl;
    return 0;
}

/************************************************
           Definitions for main.cpp
************************************************/
void displayMenu()
{
    // COMPLETE
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
    // TODO
    head = NULL;
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */


// Insert a new country with name countryName in the linked list after the country pointed to by previous.
//MEAING THIS PARAMATER OF PREVOUS THE NEXT ADDRESS OF THIS PREVIOUS NODE
void CountryNetwork::insertCountry(Country* previous, string countryName)
{
    if (previous == NULL) // IN CASE OF EMPTY LIST  
    {
        Country* temp = new Country; 
        temp -> name = countryName;  
        temp -> next = head;           
        head = temp;                    
        
        cout << "adding: " << countryName << " (HEAD)" << endl;
    }
    else     // IF THE LIST IS NOT EMPTY
    {

        Country* temp = new Country; 
        temp->name = countryName;     
        temp->next = previous->next; 
        previous->next = temp; 

        cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
    }

}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{   
    Country* current = NULL;  
    string ArrCountry[6] = {"United States", "Canada", "Brazil", "India", "China", "Australia"}; 
   
    for ( int i = 0; i<6; i++)
    {   

        insertCountry(current, ArrCountry[i]);   

        current = searchNetwork(ArrCountry[i]); 

    }

}

/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
    Country* current = head; // Initialize current
    while (current != NULL)  
    {  
        if (current->name == countryName) 
        {
            return current;
        }
        else
        {
            current = current->next;  
        }
    }
    //cout << "Country not found" << endl;
    return NULL;
}

/*
 * Purpose: Transmit a message across the network to the
 * receiver. Msg should be stored in each country it arrives
 * at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message)
{
    Country* node = head; // Initialize current  
   // node->numberMessages = 1;
    
    Country *next1 = searchNetwork(receiver);
    if(head == NULL)
    {
        cout << "Empty list" << endl;
        return;
    }
    else if (next1 == NULL)
    {
        cout << "Country not found" << endl;
        return;
    }
    //string name = reciever;
    while (node != NULL &&  node != next1->next)
    {   
        node->message = message;
        node->numberMessages++;
        cout << node->name << " [# messages received: " << node->numberMessages << "] received: " << message << endl;
        node = node -> next;

    }

}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath()
{
    // TODO
    Country* node = head;
    if(head == NULL)
    {
        cout << "== CURRENT PATH ==" << endl;
        cout <<"nothing in path" << endl;
        cout << "===" << endl;
        return;
    }
    else
    {
        cout << "== CURRENT PATH ==" << endl;
        while (node != NULL)
        {   
            cout << node->name << " -> ";
            node = node -> next;
        }
        cout << "NULL" << endl;
        cout << "===" << endl;
    }
        
}