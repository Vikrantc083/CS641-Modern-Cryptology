The cryptosytem used in this level is **EAEAE attack** which is a weak form of SASAS(Substitution and Symmetric Algorithm Substitution) attack. 

In this cryptosystem we make use of two transformations.First transformation used is a linear transformation given by an invertible 8x8 key matrix A with the elements which 
we taken from 𝐹<sub>128</sub>​ field.Second transformation is an exponentiation transformation given by a 8 x 1 vector E 
whose elements are numbers between 1 and 126. 

E is applied on a block by taking the 𝑖<sup>th</sup> element of the block and raising it to the power given by 𝑖<sup>th</sup> element in E.
Both E and A transformations are on the field 𝐹<sub>128</sub> .In this cryptosystem we apply the transformation in the sequence EAEAE on the input 
block to obtain the output block.Both E and A are part of the Key.This is the reason this cryptosystem is known as EAEAE cyptosystem.The EAEAE is 
a weak form of **SASAS** (Substitution and Symmetric Algorithm Substitution) attack.It is a variant of AES cipher
