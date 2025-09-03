#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

void listContacts(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0)
    {
        printf("\n\033[1;31mNo contacts to display!!!!!!!!\033[0m\n");
        return;
    }
    printf("\n\033[1;35m===========================contacts============================\033[0m\n");
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if (strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
    printf("\n\033[1;34m %s  %-20s  %-18s   %-23s  \033[0m\n","No","Name","Phone","Email");
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf(" %-3d %-20s", i + 1,addressBook->contacts[i].name);
        printf("%-20s",addressBook->contacts[i].phone);
        printf("%-s\n", addressBook->contacts[i].email);
    }
    printf("\n\033[1;35m===============================================================\033[0m\n");
}
    


void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    FILE* fptr = fopen("contacts.txt", "r"); 
    if (fptr == NULL)
    {
        printf("\n\033[1;31mUnable to open file\033[0m\n");
        return;
    }
    char name[100], phone[30], email[100];
    int i = 0;
    while (fscanf(fptr, "%99[^,],%29[^,],%99[^\n]\n", name, phone, email) == 3)
    {
        strcpy(addressBook->contacts[i].name, name);
        strcpy(addressBook->contacts[i].phone, phone);
        strcpy(addressBook->contacts[i].email, email);
        i++;
    }
    addressBook->contactCount = i;

    fclose(fptr); 
}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS) 
    {
        printf("\n\033[1;31Address book is full. Cannot add more contacts.\033[0m\n");
        return;
    }

	char temp[100];
    Contact *newContact = &addressBook->contacts[addressBook->contactCount];

    //For user entering a name 
    while(1)
    {
        printf("Enter the Name :");
        scanf(" %[^\n]", temp);
       

        if(is_valid_name(temp))
        {
            strcpy(newContact->name,temp);
            break;
        }
        else
        {
            printf("\n\033[1;31mInvalid Name! Only characters are allowed\033[0m\n");
        }

    }
    
    while(1)
    {
        printf("Enter a Mobile number : ");
        scanf(" %s", temp);
        getchar();
        if (isDuplicatePhone(addressBook,temp))
        {
        printf("\n\033[1;31mInvalid phone number! This number already exists.\033[0m\n");
        continue;
        }
        if(is_valid_phone(temp))
        {
            strcpy(newContact->phone,temp);
            break;
        }
        else
        {
            printf("\n\033[1;31mInvalid Phone number! Only digits are allowed\033[0m\n");
        }
    }

    while(1)
    {
        printf("Enter a Email-ID : ");
        scanf(" %s", temp);
        if (isDuplicateemail(addressBook,temp))
        {
         printf("\n\033[1;31mInvalid email!! This mail already exists.\033[0m\n");
         continue;
        }

        if(is_valid_email(temp))
        {
            strcpy(newContact->email,temp);
            break;
        }
        else
        {
           printf("\n\033[1;31mInvalid E-Mail!!!!\033[0m\n");
        }

    }
     addressBook->contactCount++;

    printf("\n\033[1;32mContact added successfully!\033[0m\n");
	
    

    
}

void searchContact(AddressBook *addressBook) 
{
    

    int choice;
    char search[50];
    char again;
    

    while(1)
    {

        printf("\nSearch Menu\n");
        printf("1.NAME\n");
        printf("2.PHONE NUMBER\n");
        printf("3.EMAIL\n");
        printf("4.EXIT FROM SEARCH MENU\n");
        printf("Enter your choice : ");
        scanf("%d",&choice);

        int found = 0;

        switch(choice)
        {
           
            case 1:
                printf("Enter name to search: ");
                scanf(" %[^\n]",search);
                if (!is_valid_name(search)) 
                {
                    printf("\n\033[1;31mInvalid name format!!!\033[0m\n");
                    break;
                }
                
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strncasecmp(addressBook->contacts[i].name, search, strlen(search)) == 0)
                    {
                         if (!found)
                       {
                        printf("\033[1;32Contact is exists\033[0m");
                        printf("\n\033[1;33m----------------> Search Results <--------------------\033[0m");
                         printf("\n\033[1;34m%-3s  %-20s  %-18s   %-23s\033[0m\n","No", "Name", "Phone", "Email");
                        }
                        printf(" %-3d %-20s", i + 1,addressBook->contacts[i].name);
                        printf("%-20s",addressBook->contacts[i].phone);
                        printf("%-s\n", addressBook->contacts[i].email);
                        printf("\n");
                        found = 1;
                    }
                }
                if (found == 0)
                {
                    printf("\n\033[1;31m No contact found with the name '%s'.\033[0m\n", search);
                }
                break;

            case 2:
                printf("Enter Phone Number to search: ");
                scanf(" %[^\n]",search);
                if (!is_valid_phone(search)) 
                {
                    printf("\n\033[1;31mInvalid Phone Number  format!!!\033[0m\n");
                    break;
                }
                
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strncasecmp(addressBook->contacts[i].phone, search, strlen(search)) == 0)
                    {
                        if (!found)
                       {
                        printf("\033[1;32Contact is exists\033[0m");
                        printf("\n\033[1;33m----------------> Search Results <--------------------\033[0m");
                         printf("\n\033[1;34m%-3s  %-20s  %-18s   %-23s\033[0m\n","No", "Name", "Phone", "Email");
                        }
                        printf(" %-3d %-20s", i + 1,addressBook->contacts[i].name);
                        printf("%-20s",addressBook->contacts[i].phone);
                        printf("%-s\n", addressBook->contacts[i].email);
                        printf("\n");
                        found = 1;
                    }
                }
                if (found == 0)
                {
                    printf("\n\033[1;31mNo contact found with the Phone Number '%s'.\033[om\n", search);
                }
                break;

            case 3:
            
                printf("Enter EMAIL - ID to search: ");
                scanf(" %[^\n]",search);
                if (!is_valid_email(search)) 
                {
                    printf("\n\033[1;31mInvalid Email  format.\033[0m\n");
                    break;
                }
                
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                     if (strncasecmp(addressBook->contacts[i].email, search, strlen(search)) == 0)
                    {
                        printf("\033[1;32Contact is exists\033[0m");
                        printf("\n\033[1;33m----------------> Search Results <--------------------\033[0m");
                        printf("\n\033[1;34m %s  %-20s  %-18s   %-23s  \033[0m\n","No","Name","Phone","Email");
                        printf(" %-3d %-20s", i + 1,addressBook->contacts[i].name);
                        printf("%-20s",addressBook->contacts[i].phone);
                        printf("%-s\n", addressBook->contacts[i].email);
                        printf("\n");
                        found = 1;
                    }
                }
                if (found == 0)
                {
                    printf("\n\033[1;31mNo contact found with the EMAIL-ID '%s'.\033[0m\n", search);
                }
                break;
            
            case 4:
               printf("Exiting search menu...\n");
                return;
            
            default:
                printf("\n\033[1;31mPlease enter a valid choice (1-4).\033[om\n");
                break;


        }
        printf("\n");
        printf("\nDo you want to search again? (y/n): ");
        scanf(" %c", &again);
        getchar(); 

        if (again != 'y') 
        {
            break; 
        }
    }


}

void editContact(AddressBook *addressBook)
{
	

    int index, choice;
    char again = 'y';
    char phone[15];
    char email[50];
    char name[20];

    while (again == 'y')
    {
        printf("\nEdit Menu:\n");
        printf("1. Edit Name\n");
        printf("2. Edit Phone Number\n");
        printf("3. Edit Email-ID\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
 

        index = searchData( addressBook,choice);

        if (index >= 0 && index < addressBook->contactCount)
        {
            switch (choice)
            {
                case 1:
                    while (1)
                    {
                        printf("Enter new name:");
                        scanf(" %[^\n]", name);
                        getchar();

                        if (is_valid_name(name))
                            {
                                strcpy(addressBook->contacts[index].name, name);
                                break;
                            }
                            else
                            {
                                printf("\n\033[1;31mEnter valid name.\033[om\n");
                            }
                    }
                        break;

                case 2:
                    while (1)
                    {
                        printf("Enter new phone number: ");
                        scanf(" %14[^\n]", phone);
                        getchar();

                        if (is_valid_phone(phone))
                        {
                            strcpy(addressBook->contacts[index].phone, phone);
                            break;
                        }
                        else
                        {
                            printf("\n\033[1;31mInvalid phone number! Enter a 10-digit numeric phone number.\033[0m\n");
                        }
                    }
                    break;

                case 3:
                    while (1)
                    {
                        printf("Enter new Email-ID: ");
                        scanf(" %49[^\n]", email);  
                        getchar();

                        if (is_valid_email(email))
                        {
                            strcpy(addressBook->contacts[index].email, email);
                            break;
                        }
                        else
                        {
                            printf("\n\033[1;31mInvalid Email-ID format! Please try again.\033[0m\n");
                        }
                    }
                    break;

                default:
                    printf("\n\033[1;31mInvalid choice! Please enter 1-4.\033[0m\n");
                    continue;
            }

            printf("\n\033[1;32mEdit Successful.\033[0m\n");
        }
        else
        {
            printf("\n\033[1;31mContact not found.\033[0m\n");
        }

        printf("Do you want to edit another contact? (y/n): ");
        scanf(" %c", &again);
    
    }

    printf("Exiting edit menu.\n");


    
}

void deleteContact(AddressBook *addressBook)
{
    int index, i, choice;
    char again = 'y';

    do
    {
        printf("\nDelete Menu:\n");
        printf("1. Delete by name\n");
        printf("2. Delete by phone number\n");
        printf("3. Delete by Email-ID\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  

        index = searchData( addressBook,choice);

        if (index >= 0 && index < addressBook->contactCount)
        {
            
            for (i = index; i < addressBook->contactCount - 1; i++)
            {
                addressBook->contacts[i] = addressBook->contacts[i + 1];
            }

            addressBook->contactCount--;  

            printf("\n\033[1;32mContact deleted successfully.\033[0m\n");
        }
        else
        {
            printf("\n\033[1;31mContact not found.\033[0m\n");
        }

        
        printf("Do you want to delete another contact? (y/n): ");
        scanf(" %c", &again);
        getchar();  

    } while (again == 'y');

    printf("Exiting delete menu.\n");
}

int is_valid_name(char *name)
{
    for (int i = 0; name[i] != '\0'; i++) 
    {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' ')) 
        {
            return 0;
        }
    }
    return 1;
}

int is_valid_phone(char *phone) 
{
    int len = 0;

    for (int i = 0; phone[i] != '\0'; i++) 
    {
        if (phone[i] < '0' || phone[i] > '9')
        {
            return 0; 
        }
        len++;
    }

    if (len != 10) 
    {
        return 0; 
    }

    return 1;
}

int is_valid_email(char *email)
{
    int len = strlen(email);

    if (len < 6) 
        return 0;

    int at_count = 0;
    int at_pos = -1;
    for (int i = 0; i < len; i++) {
        if (email[i] == '@') {
            at_count++;
            at_pos = i;
        }
    }

    
    if (at_count != 1)
        return 0;

    if (at_pos == 0 || at_pos == len - 1)
        return 0;

    char *dot = strchr(email + at_pos + 1, '.');
    if (!dot)
        return 0;

    if (dot == email + len - 1)
        return 0;

    if (strcmp(email + len - 4, ".com") != 0)
        return 0;

    if (dot - (email + at_pos) < 2)
        return 0;

    if (at_pos < 1)
        return 0;

    if (len > 8) { 
        if (strcmp(email + len - 8, ".com.com") == 0)
            return 0;
    }

    return 1;
}

int searchData(AddressBook *addressBook, int choice)
{
    char search[100];
    int flag = 0;

    switch(choice)
    {
        case 1:  
{
    char phoneSearch[20];
    int matchIndexes[100];  
    int matchCount = 0;

    printf("Enter name to search: ");
    scanf(" %[^\n]", search); // space before %[ to skip newline

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, search) == 0)
        {
            if (!flag)
            {
                printf("\n\033[1;34m%-3s  %-20s  %-18s   %-23s\033[0m\n",
                       "No", "Name", "Phone", "Email");
            }

            printf(" %-3d %-20s %-18s %-23s\n",
                   i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);

            matchIndexes[matchCount] = i;  
            matchCount++;
            flag = 1;
        }
    }

    if (!flag)
    {
        printf("\n\033[1;31mName not found!\033[0m\n");
        return -1;
    }

    // If more than one match found, ask for phone number to pick the right one
    if (matchCount > 1)
    {
        printf("\nMultiple contacts found with this name.\n");
        printf("Enter the phone number of the contact to edit: ");
        scanf("%s", phoneSearch);

        for (int j = 0; j < matchCount; j++)
        {
            int idx = matchIndexes[j];
            if (strcmp(addressBook->contacts[idx].phone, phoneSearch) == 0)
            {
                return idx; // Return the index of the matched contact
            }
        }

        printf("\n\033[1;31mNo contact with that phone number found!\033[0m\n");
        return -1;
    }
    else
    {
        // Only one match — return it directly
        return matchIndexes[0];
    }
}

        case 2:  
            while(1)
            {
                printf("Enter phone number to search: ");
                scanf("%s", search);

                
                if (!is_valid_phone(search)) 
                {
                    printf("\n\033[1;31mInvalid phone number format. Try again!!\033[0m\n");
                    continue;  
                }

                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcmp(addressBook->contacts[i].phone, search) == 0)
                    {
                        printf("------------------------------------------------------\n");

                        printf("%s\n",addressBook->contacts[i].name);
                        printf("%s\n",addressBook->contacts[i].phone);
                        printf("%s\n",addressBook->contacts[i].email);

                        printf("------------------------------------------------------\n");
                        return i;
                    }
                }

                printf("\n\033[1;31mPhone number not found!\033[0m\n");
                return -1;
            }

        case 3:  
            while(1)
            {
                printf("Enter email to search: ");
                scanf("%s", search);

              
                if (!is_valid_email(search))
                {
                    printf("\n\033[1;31mInvalid email format. Try again!!!\033[0m\n");
                    continue; 
                }

                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcmp(addressBook->contacts[i].email, search) == 0)
                    {
                        printf("------------------------------------------------------\n");
                        printf("%s\n",addressBook->contacts[i].name);
                        printf("%s\n",addressBook->contacts[i].phone);
                        printf("%s\n",addressBook->contacts[i].email);
                        printf("------------------------------------------------------\n");
                        return i;
                    }
                }

                printf("\n\033[1;31mEmail not found!\033[0m\n");
                return -1;
            }

        

        default:
            printf("\n\033[1;31mInvalid choice for search!\033[0m\n");
            return -1;
    }
}
void saveContactsToFile(AddressBook *addressBook) 
{
    FILE* fptr = fopen("contacts.txt", "w"); 
    if (fptr == NULL)
    {
        printf("\n\033[1;31mUnable to open file\033[0m\n");
        return;
    }

    int count = addressBook->contactCount;

    for (int i = 0; i < count; i++) 
    {
       
        fprintf(fptr, "%s", addressBook->contacts[i].name);
        fputc(',', fptr);

        
        fprintf(fptr, "%s", addressBook->contacts[i].phone);
        fputc(',', fptr);

        
        fprintf(fptr, "%s", addressBook->contacts[i].email);
        fputc('\n', fptr);

    }
                                
    fclose(fptr); 
}
int isDuplicatePhone(AddressBook *addressBook, const char *phone)
{
    int duplicateCount = 0;

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
            duplicateCount++;
    }
    if (duplicateCount == 0)
        return 0; 
    else
        return 1;
}
int isDuplicateemail(AddressBook *addressBook, const char *mail)
{
    int duplicateCount = 0;

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, mail) == 0)
            duplicateCount++;
    }
    if (duplicateCount == 0)
        return 0; 
    else
        return 1;
}                   
