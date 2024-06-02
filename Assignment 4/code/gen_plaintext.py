import numpy as np
import random
#hexadecimal to character mapping
hexadecimal_to_character = {
    '0000': 'f',
    '0001': 'g',
    '0010': 'h',
    '0011': 'i',
    '0100': 'j',
    '0101': 'k',
    '0110': 'l',
    '0111': 'm',
    '1000': 'n',
    '1001': 'o',
    '1010': 'p',
    '1011': 'q',
    '1100': 'r',
    '1101': 's',
    '1110': 't',
    '1111': 'u'
}

character_to_hexadecimal = {y: x for x, y in hexadecimal_to_character.items()}
# Define the fixed value to be XORed with the plaintexts for the first characteristic 
XOR_value = list((bin(0x0000801000004000))[2:].zfill(64))
XOR_value = [int(x) for x in XOR_value]
plaintext_binary = []
for i in range(5000):
    temp = np.random.choice(['f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u'], size=(1, 16), replace=True)[0]
    input_binary = []
    for i in temp:
        input_binary.extend([int(a) for a in character_to_hexadecimal[i]])

    plaintext_binary.append(input_binary)
    plaintext_binary.append(list(np.bitwise_xor(input_binary, XOR_value)))

plaintexts = []

for i in range(len(plaintext_binary)):
    s = ""
    for j in range(0, 64, 4):
        binary = ''.join([str(a) for a in plaintext_binary[i][j:j+4]])
        s += hexadecimal_to_character[binary]

    plaintexts.append(s)

with open("plaintext1.txt", "w") as f:
    for plaintext in plaintexts:
        f.write(plaintext + "\n")



character_to_hexadecimal = {x:y for y,x in hexadecimal_to_character.items()}

# Define the fixed value to be XORed with the plaintexts for the second characteristic
XOR_value = list((bin(0x0000080100100000))[2:].zfill(64))
XOR_value = [int(x) for x in XOR_value]

# Generate random plaintexts in binary format
plaintext_binary = []
for i in range(5000):
    temp = np.random.choice(['f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u'],size=(1,16),replace = True)[0]
    input_binary=[]
    for i in temp:
        input_binary.extend([int(a) for a in character_to_hexadecimal[i]])

    plaintext_binary.append(input_binary)
    plaintext_binary.append(list(np.bitwise_xor(input_binary,XOR_value)))

# Convert binary plaintexts to hexadecimal format and store them in a list
plaintexts = []
for i in range(len(plaintext_binary)):
    s = ""
    for j in range(0,64,4):
        s += hexadecimal_to_character[''.join([str(a) for a in plaintext_binary[i][j:j+4]])]
    plaintexts += [s]

# Write the plaintexts to a file named "plaintexts2.txt"
with open("plaintext2.txt","w") as file:
    for plaintext in plaintexts:
        file.write(plaintext + "\n")
