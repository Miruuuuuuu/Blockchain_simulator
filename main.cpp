# include <iostream>
# include "sqlite3.h"
# include <vector>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h> // Ensure you link with -lssl -lcrypto for OpenSSL
#include <ctime>
using namespace std;

class Transaction;
class Block
{
    private:
        string blockHash;
        string previousBlockHash;
        string timestamp;
        string merkleRoot;
        int nonce;
        int difficultyLevel;
        vector<Transaction> transactions;
        
    public:
        Block(const string& prevHash, int diffLevel) : previousBlockHash(prevHash), difficultyLevel(diffLevel) {
            timestamp = getCurrentTimestamp(); // Initialize timestamp
            nonce = 0; // Initialize nonce
        }

        // Getter methods
        string getBlockHash()  
        {
             return blockHash;
        }
        string getPreviousBlockHash() 
        { 
            return previousBlockHash; 
        }
        string getTimestamp() 
        { 
            return timestamp; 
        }
        string getMerkleRoot()
        { 
            return merkleRoot; 
        }
        int getNonce() 
        {
            return nonce;
        }
        int getDifficultyLevel() 
        { 
            return difficultyLevel;
        }
        vector<Transaction> getTransactions()  
        { 
            return transactions; 
        }

        // Setter methods
        void setBlockHash(string hash) 
        { 
            blockHash = hash; 
        }
        void setMerkleRoot( string root) 
        { 
            merkleRoot = root;
        }
        void addTransaction( Transaction& txn) 
        { 
            transactions.push_back(txn);
        }

        // Utility method to get current timestamp (you can implement your own)
        string getCurrentTimestamp() 
        {
            
    /* GETTING THE CURRENT TIMESTAMP USING CTIME*/

    // Get the current time in seconds since epoch
    time_t currentTime = time(nullptr);
    
    // Convert the time to a local time struct
    tm* localTime = localtime(&currentTime);
    
    // Output the date and time
    cout << "Current date and time: ";
    // Output the year
    cout << 1900 + localTime->tm_year << "-";
    // Output the month
    cout << 1 + localTime->tm_mon << "-";
    // Output the day
    cout << localTime->tm_mday << " ";
    // Output the hour
    cout << localTime->tm_hour << ":";
    // Output the minute
    cout << localTime->tm_min << ":";
    // Output the second
    cout << localTime->tm_sec << std::endl;

    return 0;
}
        }

        // Method to calculate block hash (you can implement your own)
        string calculateBlockHash() 
        { /* TODO
            read about block hashing and hashing algorithm to complete this
         */ return ""; 
        }

        // Method to mine the block (you can implement your own)
        void mineBlock() 
        { 


    string calculateBlockHash() {
        // Combine block's data into a single string
        stringstream ss;
        ss << previousBlockHash << timestamp << merkleRoot << nonce;
        string toHash = ss.str();

        // Calculate SHA-256 hash of the combined string
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, toHash.c_str(), toHash.size());
        SHA256_Final(hash, &sha256);

        // Convert hash to a hexadecimal string
        stringstream hashString;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            hashString << hex << setw(2) << setfill('0') << (int)hash[i];
        }

        return hashString.str(); // Return the hash as a string
    }

    // Method to mine the block
    void mineBlock() {
        // Create a target string with leading zeros equal to difficulty level
        string target(difficultyLevel, '0');
        
        // Continue looping until a valid hash is found
        do {
            nonce++; // Increment the nonce to try a new hash
            blockHash = calculateBlockHash(); // Calculate the hash with the current nonce
            
            // Print current nonce and hash for debugging (optional)
            // cout << "Nonce: " << nonce << ", Hash: " << blockHash << endl;

        // Check if the hash starts with the target number of leading zeros
        } while (blockHash.substr(0, difficultyLevel) != target);

        // When a valid hash is found, print the result
        cout << "Block mined: " << blockHash << endl;
    }
};


        
        
int main() {
    // Create the genesis block with difficulty level 4
    Block genesisBlock("0", 4); 
    // Mine the genesis block
    genesisBlock.mineBlock(); 

    return 0;
}
