#include <io.h>
#include <type.h>
#include <serial.h>

UPointer UARTInit(void) {
    outb(COM_BASE+1, 0x0);        // disable intrs
    outb(COM_BASE+3, 0x80);       // enable Divisor Latch Access Bit, for custom baud
    outb(COM_BASE+0, 0x1);        // Divisor - low byte (115200 / divisor = baud)
    outb(COM_BASE+1, 0x0);        // Divisor - high byte (our baud is 115200, i'm the speed!)
    outb(COM_BASE+3, 0x3);        // 8 bit TX/RX, no parity, 1 stop(AAAAAAA OOOOOOO)
    outb(COM_BASE+2, 0b11000111); // what the f*ck is this? sources of JokelaOS will say: 'Enable FIFO(ЭТО ИМБА ЛЮТАЯ), clear, 14-byte threshold'
    //outb(COM_BASE+4, 0xB);        // enable intrs!
    // we're ready to put the letters, i hope
}

static Unsig8 IsUARTReady() {
    return inb(COM_BASE + 5) & 0x20;
    // ! return value:
    //   busy : 0
    //   free : 1
}

UPointer OutC(JustAChar ch) {
    // waiting for UART(zastavlyat' zhdat' neprelichno)
    // ЧТОБ ВЫ ЗНАЛИ Я ЗА 10 СЕКУНД ПОНЯЛ ЧТО ЭТО
    while (!IsUARTReady());
    outb(COM_BASE, ch);
}

UPointer OutS(String s) {
    while (*s) {
        if (*s == '\n') 
            OutC('\r');
        OutC(*s);
        s++;
    }
}
