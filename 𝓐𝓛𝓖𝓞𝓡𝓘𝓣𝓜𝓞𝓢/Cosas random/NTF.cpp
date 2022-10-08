#include<iostream>
#include<string>
using namespace std;

//--------------------------------------------CLASE TOKENS------------------------------------------//
template <typename T, typename T2>
class Tokens{
    T Nft;
    T2 Token;

public:
    Tokens(T n, T2 t) {
        Nft = n;
        Token = t;
    }
    
    Tokens(){
    }
    
    void setNft(T n){
        Nft = n;
    }
    
    void setToken(T2 t){
        Token = t;
    }
    
    T getNft(){
        return Nft;
    }
    
    T2 getToken(){
        return Token;
    }
    
    Tokens& operator=(const Tokens& f) { 
		setNft(f.Nft);
		setToken(f.Token);
		return *this; 
	}
};

//---------------------------------------------CLASE HASH--------------------------------------------//
template <typename T, typename T2>
class Hash{
    int size;
    int capacity;
    Tokens<T, T2>* v;

public:
    Hash(){
        size = 0;
        capacity = 10;
        v = new Tokens<T, T2>[capacity];
    }
    
    Hash(int cap){
        size = 0;
        capacity = cap;
        v = new Tokens<T, T2>[capacity];
    }

    bool HasToken(Tokens<T, T2> t){
        for(int i = 0; i<size; i++){
            if (v[i].getToken() == t.getToken()){
                return true;
            }
        }
        return false;
    }
    
    void corrimiento_der(int i){
        for(int j = size; j>i; j--){
            v[j] = v[j-1];
        }
    }
    
    T2 hash(T nft){
        char c = 0;
        int result = 0;
        for(int i = 0; i<nft.length(); i++){
            c = nft[i];
            result+=c;
        }
        return result;
    }
    
    T2 reHash(T nft){
        T2 Token = hash(nft);
        Tokens<T, T2> m = Tokens<T, T2>(nft, Token);
        while(HasToken(m) == true){
            if(Token%2 != 0){
                Token = 3*(Token) + 1;
                m.setToken(Token);
            }else if(Token%2 == 0){
                Token = Token/2;
                m.setToken(Token);
            }
        }
        return Token;
    }
    
    void increase_capacity(){
        Tokens<T, T2>* v1 = new Tokens<T, T2>[2*capacity];
        for (int i = 0; i < size; i++){
            v1[i] = v[i];
        }
        delete[] v; //Borra el vector antiguo
        v = v1;
    }
    
    void push(T nft){
        T2 Token = hash(nft);
        Tokens<T, T2> ph = Tokens<T, T2>(nft, Token);
        
        if(HasToken(ph) == true){
            Token = reHash(nft);
            ph.setToken(Token);
        }
        if (size >= capacity){ 
            increase_capacity();
        }
    
        if(size==0){
            v[size] = ph;
            size++;
        }else{
            int flag = 0;
            for(int i = 0; i<size; i++){
                if(ph.getNft()<v[i].getNft()){
                    corrimiento_der(i);
                    v[i] = ph;
                    flag = 1;
                    break;
                }
            }
            if(flag == 0){
                v[size] = ph;
            }
            size++;
        }  
    }

    T2 find(T nft){
        int left = 0;
        int right = size-1;
        while(left <= right){
            int mid = (right+left)/2;;
            if(v[mid].getNft() == nft){
                return v[mid].getToken();
            }
            else{
                if(v[mid].getNft()>nft){
                    right = mid-1;
                }
                else{
                    left = mid+1;
                }
            }    
        }
        return NULL;
    }
    
    void print() {
        for (int i = 0; i <size; i++) {
            cout << "(" << v[i].getNft() << ", " << v[i].getToken() << ")" << "\n";
        }
        cout<<endl;
    }
};

class NFT{
    string nft1;
    int NFT1_precio;
    string nft2;
    int NFT2_precio;
    string nft3;
    int NFT3_precio;
    
public:
 //-------------------------------------------CONSTRUCTOR-----------------------------------------//
    NFT() {
        nft1 = "8888888888888888888888888888888888888888888888888888888 8888888888__________________888888888888888888888888888 88888888___8888888888888888______8888888888888888888888 88888888__88_____________888888____88888888888888888888 888888__888___________________8888____88888888888888888 88888__888_______________________8888___888888888888888 8888__88____________________________888___8888888888888 888__8_________________________________88__888888888888 88__8____________________________________88__8888888888 8__88_____________________________________88___88888888 8__88______________________888888___________88___888888 8__88________8888_________88___88____________88___88888 8__88_______88_8888_______888_888_____________888__8888 8__88______88___888________88888________________88__888 8_888______8888888_______________________________8__888 8_88_____________________________________________88__88 8_88______________________________________________88_88 8_88______________________________________________88__8 8_88______________________________________________88__8 8_88_______________________________________________8__8 8_88_______________________________________________8__8 8_88_______________________________________________8__8 8_88_______________________________________________8_88 88_88____________________________________88________8_88 88__8_______________88888888888888888888888________8_88 88__88______________8888888888888888888____________8_88 888__88______________88888888______________________8_88 8888__88___________________________________________8_88 88888__888________________________________________88_88 888888___88_______________________________________8_888 8888888___88_____________________________________88_888 888888888__8888________________________________88___888 8888888888____8888___________________________888__88888 888888888888_____8888_____________________8888___888888 888888888888888_____88888888888____88888888____88888888 8888888888888888888_________________________88888888888 888888888888888888888888888888____888888888888888888888 888888888888888888888888888888____888888888888888888888";
        NFT1_precio = 450;
        nft2 = "$$$_____$$$$$$$_$$$$$$$_$$$_______$$$_$$$$$$$$$$ $$$____$$$____$$$____$$$_$$$_____$$$__$$$_______ $$$____$$$_____$_____$$$_$$$_____$$$__$$$_______ $$$_____$$$_________$$$___$$$___$$$___$$$$$$$$__ $$$______$$$_______$$$_____$$$_$$$____$$$_______ $$$_______$$$_____$$$______$$$_$$$____$$$_______ $$$$$$$$$___$$$$$$$_________$$$$$_____$$$$$$$$$$";
        NFT2_precio = 1000;
        nft3 = "____________$_______________$___________ __________$$_________________$$_________ _________$$___________________$$________ ________$$_____________________$$_______ ________$$_____________________$$_______ ________$$_____________________$$_______ _________$$___________________$$________ _____$$__$$___________________$$__$$____ ____$$___$$___________________$$___$$___ ___$$_____$$_________________$$_____$$__ ___$_______$$$_____________$$$_______$__ ___$$_______$$$___________$$$_______$$__ ___$$$_______$$$__$$$$$__$$$_______$$$__ ____$$$$$$____$$$$$$$$$$$$$___$$$$$$$___ _________$$$$$$$$$$$$$$$$$$$$$$_________ ____$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$____ ___$$$_$$$$$$$$$$$$$$$$$$$$$$$$$$_$$$___ __$$$_________$$$$$$$$$$$$_________$$$__ _$$_________$$$$$$$$$$$$$$$$$________$$_ _$$_____$$$$$$$$$$$$$$$$$$$$$$$$_____$$_ $$_____$$$__$$$$$$$$$$$$$$$$__$$$_____$$ _$$____$$___$$$$$$$__$$$$$$$___$$____$$_ __$____$$___$$$$$$$__$$$$$$$___$$____$__ ___$___$$___$$$$$$$$$$$$$$$$___$$___$___ ____$__$$____$$$$$$$$$$$$$$____$$__$____ _______$$_____$$$$$$$$$$$$_____$$_______ _______$$_______$$$$$$$$_______$$_______ ________$$____________________$$________";
        NFT3_precio = 2500;
    }    
//------------------------------------------------METODOS-----------------------------------------//
    void exhibicion(){
        cout<<
        if(i == "nft1"){
            for(int j = 0; j<nft1.length(); j++){
                if(nft1[j] == 32){
                    cout<<endl;
                }else{
                    cout<<nft1[j];
                }
            }
            cout<<endl<<endl<<"¡𝐄𝐥 𝐩𝐫𝐞𝐜𝐢𝐨 𝐞𝐬 𝐝𝐞: "<<NFT1_precio<<" 𝐁𝐓𝐂!"<<endl;
        }else if(i == "nft2"){
            for(int j = 0; j<nft2.length(); j++){
                if(nft2[j] == 32){
                    cout<<endl;
                }else{
                    cout<<nft2[j];
                }
            }
            cout<<endl<<endl<<"¡𝐄𝐥 𝐩𝐫𝐞𝐜𝐢𝐨 𝐞𝐬 𝐝𝐞: "<<NFT2_precio<<" 𝐁𝐓𝐂!"<<endl;
        }else if(i == "nft3"){
            for(int j = 0; j<nft3.length(); j++){
                if(nft3[j] == 32){
                    cout<<endl;
                }else{
                    cout<<nft3[j];
                }
            }
            cout<<endl<<endl<<"¡𝐄𝐥 𝐩𝐫𝐞𝐜𝐢𝐨 𝐞𝐬 𝐝𝐞: "<<NFT3_precio<<" 𝐁𝐓𝐂!"<<endl;
        }
    }
    
    void comprar(){
        int c;
        Hash<string, int> Tokens_ = Hash<string, int>();
        Tokens_.push(nft1);
        Tokens_.push(nft2);
        Tokens_.push(nft3);
        cout<<"¿𝐐𝐮𝐞 𝐧𝐟𝐭 𝐝𝐞𝐬𝐞𝐚 𝐜𝐨𝐦𝐩𝐫𝐚𝐫?"<<endl;
        cin>>c;
        
        if(c == 1){
            cout<< "𝐅𝐞𝐥𝐢𝐜𝐢𝐝𝐚𝐝𝐞𝐬 𝐩𝐨𝐫 𝐬𝐮 𝐜𝐨𝐦𝐩𝐫𝐚🎉"<<endl<<"𝐒𝐮 𝐓𝐨𝐤𝐞𝐧 𝐞𝐬: "<<Tokens_.find(nft1)<<endl;
        }else if(c == 2){
            cout<< "𝐅𝐞𝐥𝐢𝐜𝐢𝐝𝐚𝐝𝐞𝐬 𝐩𝐨𝐫 𝐬𝐮 𝐜𝐨𝐦𝐩𝐫𝐚🎉"<<endl<<"𝐒𝐮 𝐓𝐨𝐤𝐞𝐧 𝐞𝐬: "<<Tokens_.find(nft2)<<endl;
        }else if(c == 3){
            cout<< "𝐅𝐞𝐥𝐢𝐜𝐢𝐝𝐚𝐝𝐞𝐬 𝐩𝐨𝐫 𝐬𝐮 𝐜𝐨𝐦𝐩𝐫𝐚🎉"<<endl<<"𝐒𝐮 𝐓𝐨𝐤𝐞𝐧 𝐞𝐬: "<<Tokens_.find(nft3)<<endl;
        }
    }
};

int main(){
    NFT t = NFT();
    t.comprar();
    return 0;
}
