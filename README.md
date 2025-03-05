# OS Chat System  

## 📌 Overview  
OS Chat System is a simple inter-process communication (IPC) chat application using **Named Pipes (FIFO)** in C. It enables multiple users to send and receive messages efficiently within a local Linux or WSL environment.  

## ⚡ Features  
- ✅ Real-time message sending and receiving  
- ✅ Uses Named Pipes (FIFO) for communication  
- ✅ Compatible with **WSL (Windows Subsystem for Linux) and Linux**  
- ✅ Lightweight and efficient  

## 🚀 Installation & Usage  

### **Step 1: Clone the Repository**  
```sh  
git clone https://github.com/noumancomputes/OS-Chat-System.git  
cd OS-Chat-System  
```

### **Step 2: Compile the Code**  
Use `gcc` to compile:  
```sh  
gcc Chat_Sender.c -o sender  
gcc Chat_Receiver.c -o receiver  
```

### **Step 3: Run the Chat System**  

#### **In One Terminal: Start the Receiver**  
```sh  
./receiver  
```

#### **In Another Terminal: Start the Sender**  
```sh  
./sender  
```

Now, type messages in the sender terminal, and they will appear in the receiver terminal.

## ⚠️ Requirements  
- Linux or **Windows Subsystem for Linux (WSL)**  
- GCC Compiler (`sudo apt install gcc` for Ubuntu/WSL)  

## 📚 License  
This project is **MIT Licensed**. Feel free to use and modify it.  