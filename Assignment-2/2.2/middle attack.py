# ujjwal kumar
# cs23btnsk11002


import os,binascii
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from aesLongKeyGen16 import *

#Subroutine for encryption
def aesEncrypt(message_bytes,cipher):
    encryptor = cipher.encryptor()
    ciphertext = encryptor.update(message_bytes) + encryptor.finalize()
    return ciphertext
#Subroutine for decryption
def aesDecrypt(message_bytes,cipher):
    decryptor = cipher.decryptor()
    plaintext = decryptor.update(message_bytes) + decryptor.finalize()
    return plaintext


firstplaintext = ["Hydrodynamometer"]
ciphertexts = ["ea7f6a9b8ca5641e5c574000342a6322"]
strange_cipher = "c85afb6a2947ee3497ddf2b10e3ac81b"
dictionary = {}


for i in range(2**16):
      
    shortKeyBytes = i.to_bytes(2, byteorder='big') #seq
    shortKey1=bytearray(shortKeyBytes)


    longKey1=expandKey(shortKey1)


    cipher1 = Cipher(algorithms.AES(longKey1), modes.ECB())
    
    for message in firstplaintext:
        message_bytes=message.encode('UTF-8')
        #Encrypt with key1
        ciphertext = aesEncrypt(message_bytes,cipher1) 
        dictionary[ciphertext.hex()] = shortKeyBytes
 
# print(len(dictionary))
flag = False
for i in range(2**16):    
    
    shortKeyBytes = i.to_bytes(2, byteorder='big') #seq
    shortKey1=bytearray(shortKeyBytes)


    longKey1=expandKey(shortKey1)

    cipher1 = Cipher(algorithms.AES(longKey1), modes.ECB())
    #cipher2 = Cipher(algorithms.AES(longKey2), modes.CBC(iv))
    
    for ciphertext in ciphertexts:

        
        #decryptor=cipher.decryptor()
        secretcipher=bytes.fromhex(ciphertext)
        #plain=decryptor.update(secretcipher)+decryptor.finalize()
        ciphertext2=aesDecrypt(secretcipher,cipher1)
        if ciphertext2.hex() in dictionary.keys():
            second_key = shortKeyBytes
            first_key = dictionary[ciphertext2.hex()]
            print("1st key: ",dictionary[ciphertext2.hex()].hex())
            print("2nd key: ",shortKeyBytes.hex())
            
            flag=True
            break
    if flag:
        break


secretcipher=aesDecrypt(bytes.fromhex(strange_cipher),Cipher(algorithms.AES(expandKey(second_key)), modes.ECB()))
plain=aesDecrypt(secretcipher,Cipher(algorithms.AES(expandKey(first_key)), modes.ECB()))
print("Secret plain text is: ",plain.decode('utf-8'))


    


        
        