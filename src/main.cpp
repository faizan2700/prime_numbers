// Online C++ compiler to run C++ program online
#include <iostream> 
#include <vector> 
#include <bitset> 
#include <thread>  
#include <atomic> 
#include <mutex> 

using namespace std;

const int block_size = 1e6;  

class PrimeCounter{ 
   public: 
   std::atomic<long long> primes_counter; 
   int total_blocks = 10000; 
   int total_threads = 1; 
   vector<long long> primes; 
   vector<long long> ps; 
   std::mutex primes_vector_mutex; 
   PrimeCounter(){  
       primes_counter = 0; 
       vector<std::thread> ts; 
       setup(); 
       int current_starting = block_size; 
       for(int i = 0; i < total_threads; i++) { 
          std::thread t1(&PrimeCounter::calculate, this, i, current_starting); 
          if(i==0) current_starting += (total_blocks-1)*block_size; 
          else current_starting += total_blocks*block_size; 
        ts.push_back(std::move(t1)); 
       }
       for(int i = 0; i < total_threads; i++) { 
           ts[i].join(); 
       }
   }
   
   void calculate(int thread_id, long long low){ 
        std::bitset<block_size> composite; 
        long long x = low+1, y = low + block_size; 
        if(x<=2) x = 2; 
        int starting_block_num = 1; 
        if(thread_id==0) starting_block_num = 2; 
        for(int i = starting_block_num; i <= total_blocks; i++) { 
            for(int j = 0; j < (int)ps.size() && 1LL*ps[j]*ps[j] <= y; j++){
                long long start = ((x+ps[j]-1)/ps[j])*ps[j]; 
                for(long long k = start; k <= y; k+=ps[j]){
                    composite[k-x]=1; 
                }
            }
            
            for(long long j = x; j <= y; j++){
                if(composite[j-x]!=1) { 
                    primes_counter += 1;  
                } 
            }
            composite.reset(); 
            primes.clear(); 
            x = y+1; 
            y = y + block_size; 
        }
   }
   
   void setup(){ 
       std::bitset<block_size> composite; 
       for(int i = 2; i <= block_size; i++) { 
           if(composite[i] == 1) continue; 
           this->ps.push_back(i); 
           primes.push_back(i); 
           primes_counter += 1; 
           if(1LL*i*i > block_size) continue; 
           for(int j = i*i; j <= block_size; j+=i){
               composite[j] = 1; 
           }
       }
   }
}; 

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    PrimeCounter p = PrimeCounter();
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    cout << "Execution Time: " << duration.count() << " seconds" << endl;

    cout << "primes_counter: "<< p.primes_counter << endl; 
    
    return 0; 
}

