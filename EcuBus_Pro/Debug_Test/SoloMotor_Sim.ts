import { output } from "ECB";

Util.OnCan(0x601, (msg) => {
    console.log(msg); // Log the received message to the console
    msg.data[0] = 0x60; // Set the first byte of the message data to 0x60
    msg.data[4] = 0x00; // Set the first byte of the message data to 0x00
    msg.data[5] = 0x00; // Set the first byte of the message data to 0x00
    msg.data[6] = 0x00; // Set the first byte of the message data to 0x00
    msg.data[7] = 0x00; // Set the first byte of the message data to 0x00
    msg.id = 0x581; // Set the message ID to 0x581
    msg.dir = "OUT"; // Set the message direction to "OUT"
    output(msg);
})

Util.OnCan(0x602, (msg2) => {
    msg2.data[0] = 0x60; // Set the first byte of the message data to 0x60
    msg2.data[4] = 0x00; // Set the first byte of the message data to 0x00
    msg2.data[5] = 0x00; // Set the first byte of the message data to 0x00
    msg2.data[6] = 0x00; // Set the first byte of the message data to 0x00
    msg2.data[7] = 0x00; // Set the first byte of the message data to 0x00
    msg2.id = 0x582; // Set the message ID to 0x582
    msg2.dir = "OUT"; // Set the message direction to "OUT"
    output(msg2);
})   
