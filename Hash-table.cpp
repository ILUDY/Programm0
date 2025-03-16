#include <iostream>
#include <bitset>
#include<vector>
#include <string>
class Animal{
    public:
    int paws_amount;
    std::string colour;
    std::string name;
};
struct DPair{
    int K;
    bool status;
    std::string V;
    DPair():K(-1),status(false),V(""){};
    DPair(int k, bool s, const std::string v) : K(k), status(s), V(v) {}
};
class hash_table{//создание таблицы без рехешировани, без возможности хранить под одним ключом несколько значений
    size_t size;
    size_t cur_size;
    const int c1=1;
    const int c2=3;
    std::vector <DPair> table;
    public:
    hash_table(size_t s=10): size(s),cur_size(0),table(s){};
    int Hash(const Animal& A){//(первый символ окраса+кол-во лап-> биты )->int
        int num=A.paws_amount;
        std::string str=A.colour;
        std::bitset<8> bit1 (str[0]);
        std::bitset<8> bit2 (num);
        std::bitset<16> res=bit1.to_ulong()+bit2.to_ulong();
        return int(res.to_ulong())%size;
    }
    int quadr_probe(int ind,int i){
        return(ind+c1*i+c2*i*i)%size;
    }
    void insert(const Animal& A){//ВВОД + квадратичное пробирование
        int hash= Hash(A);
        int attmp=0;
        int ind;
        std::string value=A.name;
        while(attmp<size){
            ind=quadr_probe(hash,attmp);
            if(!table[ind].status){
                table[ind] = DPair{hash,true,value};
                cur_size++;
                return;
            }
            if(table[ind].K==hash && table[ind].V == value){
                    std::cout<<"pair exists"<<std::endl;
                    return;
                }
            ++attmp;
            }
        std::cout<<"Table is overloaded"<<std::endl;
    }
    void print(){
        for(size_t ind=0;ind<size;++ind){
            if(table[ind].status){
                std::cout<<ind<<"{ "<<table[ind].K<<" , "<<table[ind].V<<" }"<<std::endl;
            }
            else{
                std::cout<<ind<<" "<<"EMPTY"<<std::endl;
            }
        }
    }
    int find(const Animal& A){
        int hash = Hash(A);
        int attmp = 0;
        int ind;
        std::string value = A.name;
        while (attmp < size) {
            ind = quadr_probe(hash, attmp);
            if (table[ind].status && table[ind].K == hash && table[ind].V == value) {
                std::cout << "ELEMENT WAS FOUND: " << ind << std::endl;
                return ind;
            }
            if (!table[ind].status) {
                std::cout << "NO SUCH ELEMENT" << std::endl;
                return -1;
            }
            ++attmp;
        }
        std::cout << "NO SUCH ELEMENT" << std::endl;
        return -1;
    }
    void delete_element(const Animal& A){
        int ind=find(A);
        if(ind!=-1){
            table[ind]={-1,false,""};
            cur_size--;
        }
    }

};
void test() {
    hash_table ht(7);
    // Тест 1: Вставка элементов
    std::cout << "Тест 1: Вставка элементов" << std::endl;
    Animal a1 = {4, "Red", "Fox"};
    Animal a2 = {2, "Blue", "Bird"};
    Animal a3 = {4, "Green", "Frog"};
    Animal a4 = {4, "Yellow", "Lion"};
    Animal a5 = {0, "Purple", "Snake"};
    Animal a6 = {4, "White", "Dog"};
    Animal a8 = {5, "Violet", "Rex"};
    ht.insert(a1);
    ht.insert(a2);
    ht.insert(a3);
    ht.insert(a4);
    ht.insert(a5);
    ht.insert(a6);
    ht.print();
    std::cout << std::endl;
    std::cout << std::endl;
    // Тест 2: Поиск элементов
    std::cout << "Тест 2: Поиск элементов" << std::endl;
    int result = ht.find(a1);
    result = ht.find(a2);
    std::cout << std::endl;
    std::cout << std::endl;
    // Тест 3: Удаление элементов
    std::cout << "Тест 3: Удаление элементов" << std::endl;
    ht.delete_element(a1);
    std::cout << "После удаления ключа a1:" << std::endl;
    ht.print();
    std::cout << std::endl;
    std::cout << std::endl;
    // Тест 4: удаление несуществующего элемента
    std::cout << "Тест 4: Удаление несуществующего элемента" << std::endl;
    ht.delete_element(a8);
    std::cout << "После попытки удаления a8:" << std::endl;
    ht.print();
}
int main(){
    test();
    return(0);
}