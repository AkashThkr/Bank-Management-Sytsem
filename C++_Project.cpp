#include<iostream>
#include<fstream>
#include<string>

class Account {
    private:
    int accountNo;
    char name[20];
    int deposit;
    char mail[20];
    int password;
    int admpass;
    
    public:
    int create_account(int accountNo){
    	this->accountNo = accountNo;
    	std::cout<<"\n\nEnter Your Name : ";
		std::cin.ignore();
		std::cin.getline(name,50);
		std::cout<<"\n\nEnter Your Password.   : ";
		std::cin>>password;
		std::cout<<"\n\nEnter The E-Mail of The Account Holder : ";
		std::cin.ignore();
		std::cin.getline(mail,50);
		std::cout<<"\nEnter The Initial Amount To Be Deposited (Amount>=1000 ) : ";
		std::cin>>deposit;
		if(deposit>=1000){
			return 1;
		} 
		else{ 
			return 2;
		}	
    }
  
   	void show_account() const{                 
   		std::cout<<"\nAccount No. : "<<accountNo;      
		std::cout<<"\nAccount Holder Name : "<<name;;
		std::cout<<"\nAccount Holder E-MailId :"<<mail;
		std::cout<<"\nBalance amount : "<<deposit;
   	}		    
		    
   	int modify(){	                         		    
		std::cout<<"\nAccount No. : "<<accountNo;
		std::cout<<"\nEnter New Account Holder Name : ";
		std::cin.ignore();
		std::cin.getline(name,50);
		std::cout<<"\n\nEnter Your Password.   : ";
		std::cin>>password;
		std::cout<<"\n\nEnter The New E-Mail of The Account Holder : ";
		std::cin.ignore();
		std::cin.getline(mail,50);
		std::cout<<"\nEnter The Initial Amount To Be Deposited (Amount>=1000 ) : ";
		std::cin>>deposit;
		if(deposit>=1000){ 
			return 1;
		}	
    	        else{
			return 2;
		}	
	}	    
	
	void dep (int z){
		deposit+=z; 
	}             		    
   	
	void draw(int z){
		deposit-=z; 
	}
           		    
        int retacc() const{ 
	   return password; 
	}
   
        int retac()const { 
	   return accountNo;
	}
    
	int retdeposit()const{ 
		return deposit;
	}

	void detail() const { 
		std::cout<<password<<"       "<<accountNo<<"         "<<name<<"              "<<deposit <<std::endl; 
	}	     

   	void admin(){ 
		admpass=007;
	}
   
   	int readm(){   
		if(admpass==007){	
		   return admpass;
		} 
	}     
}; //class ends here;

void admin_password(int n) {
	Account Ac;
	std::fstream outFile;
	outFile.open("account.dat",std::ios::binary|std::ios::app);
	Ac.admin();
	outFile.write( (char*) &Ac, sizeof(Account));
	outFile.close();
}
 
void write_account() {	
	int i, n, account=100;
	std::cout<<"\n\nHow many Account You Want To Create ";
	std::cin>>n;
	for(i=1;i<=n;i++)  {
		Account Ac;
		int doOpenAccount = Ac.create_account(account);
		if(doOpenAccount == 1) {
			std::ofstream outFile;
			outFile.open("account.dat",std::ios::binary|std::ios::app);
			outFile.write( (char*) &Ac, sizeof(Account ) );
			outFile.close();
			std::cout<<"\n\n\nAccount Created ";
			std::cout<<"\nYour  account No. : ";
			std::cout<<account;
			account++;
		} 
		else{
			std::cout<<"\n\n\nAccount Not Created..(* Initial Deposit>=1000) >>> Try Again..";
		}
	}
}

void display_sp(int n,int n2) {	
	Account Ac;
	bool flag=false;
	std::ifstream inFile;
	inFile.open("account.dat",std::ios::binary);
	if(!inFile){
		std::cout<<"Account could not be open !! Press any Key...";
		return;
	}
	std::cout<<"\n Account Balance Details\n";
	while(inFile.read( (char*) &Ac, sizeof(Account))){
		if(Ac.retac()==n){
			if(Ac.retacc()==n2){
				Ac.show_account();
				flag=true;
			}
		}
	}
	inFile.close();
	if(flag==false){
		std::cout<<"\n\nAccount number does not exist";
	}	
}

void modify_account(int n,int n2) {  
	bool found=false;
	Account Ac;
	std::fstream File;
	File.open("account.dat",std::ios::binary|std::ios::in|std::ios::out);
	if(!File){
		std::cout<<"Account could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false){
		File.read( (char*) &Ac, sizeof(Account));
		if(Ac.retac()==n){
			if(Ac.retacc()==n2){
				Ac.show_account();
				std::cout<<"\n\nEnter The New Details of account"<<std::endl;
				Ac.modify();
				int pos=(-1)*static_cast<int>(sizeof(Account));
				File.seekp(pos,std::ios::cur);
				File.write( (char*) &Ac, sizeof(Account));
				std::cout<<"\n\n\t Account Updated";
				found=true;
			}
		}
	}	
	File.close();
	if(found==false){
		std::cout<<"\n\n Account Not Found ";
	}  	  
}

void delete_account(int n , int n2 ) {              	
	Account Ac;
	std::ifstream inFile;
	std::ofstream outFile;
	inFile.open("account.dat",std::ios::binary);
	if(!inFile){
		std::cout<<"Account could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.txt",std::ios::binary);
	inFile.seekg(0,std::ios::beg);
	while(inFile.read( (char*) &Ac, sizeof(Account))){
		if(Ac.retac()==n){
			if(Ac.retacc()==n2){
				outFile.write( (char*) &Ac, sizeof(Account));
			}
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.txt","account.dat");
	std::cout<<"\n\n\tAccount Deleted ..";
}

void display_all(int n) { 
	Account Ac;
	std::fstream inFile;
	inFile.open("account.dat",std::ios::binary|std::ios::in|std::ios::out);
	if(!inFile){
		std::cout<<"Account could not be open !! Press any Key...";
		return ;
	}
	if(Ac.readm()==n){
		std::cout<<"\n\n\t\t* Lena Dena Bank Account Holders *\n\n";
		std::cout<<"A/c no.      NAME             Balance\n\n";
		while(inFile.read( (char*) &Ac, sizeof(Account))){
			Ac.detail();
		}
		inFile.close(); 
	}
}

void deposit_withdraw(int n ,int n2 , int option) {            
	int Ammount;
	bool found=false;
	Account Ac;
	std::fstream File;
	File.open("account.dat",std::ios::binary|std::ios::in|std::ios::out);
	if(!File){
		std::cout<<"Account could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false){
		File.read( (char*) &Ac, sizeof(Account));
		if(Ac.retac()==n){
			if(Ac.retacc()==n2){
				Ac.show_account();
				if(option==1){
					std::cout<<"\n\n\tTO DEPOSITE AMOUNT ";
					std::cout<<"\n\nEnter The amount to be deposited";
					std::cin>>Ammount;
					Ac.dep(Ammount);
				}
				if(option==2){
					std::cout<<"\n\n\tTO WITHDRAW AMOUNT ";
					std::cout<<"\n\nEnter The amount to be withdraw";
					std::cin>>Ammount;
					int bal=Ac.retdeposit()-Ammount;
					if((bal<500)  || (bal<1000 )){
						std::cout<<"Sorry!.Insufficience Balance To Withddraw!";
					}	
					else{
						Ac.draw(Ammount);
					}	
				}
				int pos=(-1)*static_cast<int>(sizeof(Ac));
				File.seekp(pos,std::ios::cur);
				File.write( (char*) &Ac, sizeof(Account));
				std::cout<<"\n\n\t Account Updated: Press Enter And Check Your Balance:";
				found=true;
			}
		}
	}
        File.close();
	if(found==false){
		std::cout<<"\n\n Account Not Found ";
	}	
}

int main() {
	char ch;
	int num,num2;
	std::cout<<"* * Welcome To Dena Lena Bank * *";
	do{
		std::cout<<"\n\n\n>>>>>Banking Menu>>>>>";
		std::cout<<"\n\n01. Create A New Account.    ";
		std::cout<<"\n\n02. Cash Deposit.            ";
		std::cout<<"\n\n03. Withdrawl Cash.          ";
		std::cout<<"\n\n04. Account Balance Enquiry. ";
		std::cout<<"\n\n05. Modify/Edit An Account.  ";
	        std::cout<<"\n\n06. Accounts Holders Details (* Admin Access Only). ";
	        std::cout<<"\n\n07. Close/Delete Your Account.       ";
		std::cout<<"\n\n08. Exit From Banking Menu.  ";
		std::cout<<"\n\nPlease Select Your Option. : ";
		std::cin>>ch;
		
		switch(ch){
			case '1':
				write_account();
				break;
			case '2':
				std::cout<<"\n\n\tEnter Your Account Number . : ";
				std::cin>>num;
				std::cout<<"\n\n\tEnter Your Password . : "; 
				std::cin>>num2;
				deposit_withdraw(num,num2, 1);
				break;
			case '3':
				std::cout<<"\n\n\tEnter Your Account Number . : ";
				std::cin>>num;
				std::cout<<"\n\n\tEnter Your  Password . : "; 
				std::cin>>num2;
				deposit_withdraw(num, num2 , 2);
				break;
			case '4': 
		    	std::cout<<"\n\n\tEnter Your Account Number . : ";
				std::cin>>num;
				std::cout<<"\n\n\tEnter Your Password . : "; 
				std::cin>>num2;
				display_sp(num,num2);
				break;
			case '5':
				std::cout<<"\n\n\tEnter Your Account Number . : ";
				std::cin>>num;
				std::cout<<"\n\n\tEnter Your Password . : ";
				std::cin>>num2;
				modify_account(num,num2);	                         
				break;
			case '6':
				std::cout<<"\n\n\tEnter Admin's Password . : "; std::cin>>num;
				admin_password(num);
		    	display_all(num);
				break;
			case '7':
		 		std::cout<<"\n\n\tEnter Your Account Number . : ";
		 		std::cin>>num;
				std::cout<<"\n\n\tEnter Your Password Number . : ";
				std::cin>>num2;
		    	delete_account(num,num2);
				break;
			case '8':
				std::cout<<"\n\nThanks For Using Dena Lena Banking System";
				break;
			default : std::cout<<"\a"; std::cout<<"Please Select Any Of The Above Option : Press Enter Again..";
		}
		std::cin.ignore();
		std::cin.get();
    }while(ch!='8');
	return 0;
}
