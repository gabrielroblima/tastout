Welcome to my repository

This project is a part of a bigger development made during my 2nd year of engineering school internship. The main purpose is to offer a way to write signal parameters into a noisy digital signal. By this, after been sent, a signal can have its parameters compared to written parameters, offering a way to check the received signal.

The name Tastout came from French "T'as tout" or "Tu as tout" a way to say you have everything, it is also a pun with the word tattoo (which has the same sound) giving the idea of tattooing information into a signal.
I'd like to thank my internship tutor, M. Sébastien COUDERT, by the opportunity and give him the credits for this idea. 


# How to build the project

1. Firstly, clone this repository
   ```bash
     git clone https://github.com/gabrielroblima/tastout.git 
   ```
2. Download <a href="https://www.openai.com" target="_blank">CImg library</a>

3. Verify if you have CImg files, then compile and run the project
   ```bash
   ls ../CImg
   make all
   ```

# How does it work?

Imagine you have a noisy digital signal. What happens if you change only the least significant bit of each signal sample? It could also be considered noise, right? So in theory your signal was not changed, and no important parts were lost. This is the idea. Let's explore a simple example to easy understand. For this example, we'll suppose a signal composed by 8 values and we are going to tattoo an the minimal value as a parameter into the signal.

| Sample # | Original Decimal | Original Binary | Binary After Tattooing | Final LSB | Tattooed Value |
|:-------:|:----------------:|:----------------:|:----------------------:|:---------:|:---------------:|
|   0     |       173        |     10101101     |       10101100         |     0     |                 |
|   1     |        64        |     01000000     |       01000000         |     0     |                 |
|   2     |       255        |     11111111     |       11111111         |     1     |                 |
|   3     |        34        |     00100010     |       00100011         |     1     |                 |
|   4     |        89        |     01011001     |       01011000         |     0     |       **3**     |
|   5     |       120        |     01111000     |       01111000         |     0     |                 |
|   6     |         3        |     00000011     |       00000011         |     1     |                 |
|   7     |       202        |     11001010     |       11001011         |     1     |                 |

As you can see, the value 3 is the minimum of the signal, in ASCII it is "51" or if we convert to binary "00110011". It was tattooed into the signal formed by 8 samples. I know, in the case you have too small values, it could be a problem to change a unity, but if you work with big values, like 32 or 64 bits values, this difference will probably change nothing.

The way the library was developed, firstly converts all data to ASCII and then tattoos it into the signal.

Is recommended to use only integer data types in CImg (8, 16, 32 or 64 bits). These types where tested and validated! ;)

# Example of output
~~~{ .bash}
roberto-lima@ganl1203:~/Documents/code/tastout$ ./tastout -s false
Non tattooed data
CImg<uint16>: this = 0x7fff24fb7510, size = (8192,1,1,1) [16 Kio], data = (uint16*)0x62e4ab03a340..0x62e4ab03e33f (shared) = [ 0 0 0 0 0 0 0 0 ... 0 0 0 0 0 0 0 0 ], min = 0, max = 65535, mean = 17.3097, std = 829.553, coords_min = (0,0,0,0), coords_max = (4096,0,0,0).
Tattooed data
CImg<uint16>: this = 0x7fff24fb7510, size = (8192,1,1,1) [16 Kio], data = (uint16*)0x62e4ab03e340..0x62e4ab04233f (shared) = [ 0 1 0 1 0 1 0 0 ... 0 0 0 0 0 0 0 0 ], min = 0, max = 65535, mean = 17.3231, std = 829.553, coords_min = (0,0,0,0), coords_max = (4096,0,0,0).
Received Data
CImg<uint16>: this = 0x7fff24fb7510, size = (4,1,1,1) [8 b], data = (uint16*)0x62e4ab042900..0x62e4ab042907 (non-shared) = [ 4096 4096 65535 0 ], min = 0, max = 65535, mean = 18431.8, std = 31461.5, coords_min = (3,0,0,0), coords_max = (2,0,0,0).
