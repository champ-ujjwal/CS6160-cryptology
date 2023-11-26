# Ujjwal kumar
# cs23btnsk11002

import os
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from aesLongKeyGen24 import *

n = 5
a= True
Cipher1 = False
def expandKey(shortKey):    
    shortKeyval1=shortKey[0]
    shortKeyval2=shortKey[1]
    #Ignore the last 4 bits as given in question
    shortKeyval3=shortKey[2]&0xF0
    
    ByteA=shortKeyval1.to_bytes(1,"big")
    ByteB=shortKeyval2.to_bytes(1,"big")
    ByteC=shortKeyval3.to_bytes(1,"big")
    hexByte1=0x94
    Byte1=hexByte1.to_bytes(1,"big")
    hexByte2=0x5a
    Byte2=hexByte2.to_bytes(1,"big")
    hexByte3=0xe7
    Byte3=hexByte3.to_bytes(1,"big")
    
    longKey=bytearray(ByteA)    
    longKey.extend(Byte1)
    longKey.extend(ByteB)    
    longKey.extend(Byte2)
    
    for i in range(4,9):        
        hexByte=(longKey[i-1]+longKey[i-4])%257
        if (hexByte==256):
            hexByte=0
        Byte=hexByte.to_bytes(1,"big")              
        longKey.extend(Byte)
    longKey.extend(ByteC)   
    longKey.extend(Byte3)
    for i in range(11,16):
        hexByte=(longKey[i-1]+longKey[i-4])%257
        if (hexByte==256):
            hexByte=0
        Byte=hexByte.to_bytes(1,"big")              
        longKey.extend(Byte)    
    
    return longKey


iterations = 2**24

def KeyFind(file1, file2):
    for iteration in range(iterations):
        # Generate a random 3-byte key
        shortKeyBytes = os.urandom(3)
        shortKey = bytearray(shortKeyBytes)

        # Expand the key to 128 bits
        key = expandKey(shortKey)

        # Set up iv and cipher
        iv = b'\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0'
        cipher = Cipher(algorithms.AES(key), modes.CBC(iv))

        #check for ciphertext
        for i in range(n):
            if a == Cipher1:
                break
     # Read and decrypt messages
        decrypted_messages_list = []
        with open(file1, "r") as reader:
            ciphertexts = reader.read().split('\n')
            for ciphertext_hex in ciphertexts:
                ciphertext_bytes = bytes.fromhex(ciphertext_hex)
                decryptor = cipher.decryptor()
                decrypted_message = decryptor.update(ciphertext_bytes) + decryptor.finalize()
                decrypted_messages_list.append(decrypted_message.decode('UTF-8', errors='replace'))

        # Check if the decrypted messages match the original plaintexts
        with open(file2, "r") as reader:
            original_messages = reader.read().split('\n')

        all_messages_match = all(decrypted == original for decrypted, original in zip(decrypted_messages_list, original_messages))

        if all_messages_match:
            print("Correct key found!")
            print("Short Key found:", shortKey.hex())
            print("Long Expanded Key found:", key.hex())
            break
        else:
            print(f"{iteration} iteration gets failed. Trying the next possible key.")

    # If the loop completes without finding the correct key
    else:
        print("By Brute-force attack we can't find the key, checked all possible key.")


def decryptCipher():
        # Set up iv and cipher
    iv = b'\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0'

    # Convert the key to bytes
    key_hex = "8e94635ae87bde371e30e71d3b6b516e"
    key = bytes.fromhex(key_hex)

    cipher = Cipher(algorithms.AES(key), modes.CBC(iv))
    long_decryptor = cipher.decryptor()

    #loop through ciphertext
    for i in range(n):
        if a == Cipher1:
            break
        else:
            continue
    # Provide a valid ciphertext for the chosen key size
    ciphertext_to_decrypt = bytes.fromhex("ca6889853e3ddfaf621b87ee4966e274")

    # Decrypt the ciphertext using the long key
    decrypted_with_long_key = long_decryptor.update(ciphertext_to_decrypt) + long_decryptor.finalize()

    # Print the result
    print("Secret plain text :", decrypted_with_long_key.decode('UTF-8', errors='replace'))       

file1 = "aesCiphertexts.txt"
file2 = "aesPlaintexts.txt"

KeyFind(file1, file2)
decryptCipher()   