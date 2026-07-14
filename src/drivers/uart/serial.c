#include <io.h>
#include <type.h>
#include <serial.h>
#include <macro.h>

UPointer UARTInit
(void) {
    outb(COM_BASE+1, 0x0);        // disable intrs
    outb(COM_BASE+3, 0x80);       // enable Divisor Latch Access Bit, for custom baud
    outb(COM_BASE+0, 0x1);        // Divisor - low byte (115200 / divisor = baud)
    outb(COM_BASE+1, 0x0);        // Divisor - high byte (our baud is 115200, i'm the speed!)
    outb(COM_BASE+3, 0x3);        // 8 bit TX/RX(we don't need fucking 16-bit TX/RX at all), no parity, 1 stop(AAAAAAA OOOOOOO)
    outb(COM_BASE+2, 0b11000111); // what the f*ck is this? sources of JokelaOS will say: 'Enable FIFO(ЭТО ИМБА ЛЮТАЯ), clear, 14-byte threshold'
    outb(COM_BASE+1, 0x01);        // enable intrs!
    // we're ready to put the letters, i hope
}

static Unsig8 IsUARTReady
() {
    return inb(COM_BASE + 5) & 0x20;
    // ! return value:
    //   busy : 0
    //   free : 1
}

UPointer OutC
(JustAChar ch) {
    // waiting for UART(zastavlyat' zhdat' neprelichno)
    // ЧТОБ ВЫ ЗНАЛИ Я ЗА 10 СЕКУНД ПОНЯЛ ЧТО ЭТО
    while (!IsUARTReady());
    outb(COM_BASE, ch);
}

UPointer OutS
(String s) {
    while (*s) {
        if (*s == '\n') 
            OutC('\r');
        OutC(*s);
        s++;
    }
}

UPointer OutI
(Unsig32 n) {
    JustAChar buf[12];
    Unsig16 i = 0;

    do {
        buf[i++] = '0' + n % 10;
        n /= 10;
    } while (n > 0);
    
    while(i > 0) OutC(buf[--i]);
}

UPointer OutH
(Unsig32 n) {
    OutS("$0x");
    String digits = "0123456789ABCDEF";
    for(int i = 28; i >= 0; i -= 4) {
        OutC(digits[(n >> i) & 0xF]);
    }
}

UPointer OutB
(Unsig32 n) {
    for(Unsig8 i = 32; i > 0; --i) {
        OutC((n >> i) & 1? '1': '0');
    }
}

UPointer OutL
(Unsig64 n) {
    OutS("$0x");
    String digits = "0123456789ABCDEF";
    for(int i = 60; i >= 0; i -= 4) {
        OutC(digits[(n >> i) & 0xF]);
    }
}