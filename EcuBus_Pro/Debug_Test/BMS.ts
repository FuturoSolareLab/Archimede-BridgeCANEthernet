import { Util, CanMessage, CAN_ID_TYPE, output } from 'ECB'

// Messaggio 1 Cell voltage information
const msg1: CanMessage = {
  id: 0x04008001,
  dir: 'OUT',
  data: Buffer.from([0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]),
  msgType: {
    idType: CAN_ID_TYPE.EXTENDED,
    remote: false,
    canfd: false,
    brs: false
  }
}

// Messaggio 2 Cell temperature information
const msg2: CanMessage = {
  id: 0x04018001,
  dir: 'OUT',
  data: Buffer.from([0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]),
  msgType: {
    idType: CAN_ID_TYPE.EXTENDED,
    remote: false,
    canfd: false,
    brs: false
  }
}

// Messaggio 3 - Total information 0
const msg3: CanMessage = {
  id: 0x04028001, // <-- TODO: sostituisci con l'ID reale
  dir: 'OUT',
  data: Buffer.from([0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]),
  msgType: {
    idType: CAN_ID_TYPE.EXTENDED,
    remote: false,
    canfd: false,
    brs: false
  }
}

// Messaggio 4 Total information 1
const msg4: CanMessage = {
  id: 0x04038001, // <-- TODO: sostituisci con l'ID reale
  dir: 'OUT',
  data: Buffer.from([0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]),
  msgType: {
    idType: CAN_ID_TYPE.EXTENDED,
    remote: false,
    canfd: false,
    brs: false
  }
}

// Messaggio 5 Cell voltage statistical information
const msg5: CanMessage = {
  id: 0x04048001, // <-- TODO: sostituisci con l'ID reale
  dir: 'OUT',
  data: Buffer.from([0x00, 0x00, 0x00, 0x00, 0x88 ]),
  msgType: {
    idType: CAN_ID_TYPE.EXTENDED,
    remote: false,
    canfd: false,
    brs: false
  }
}

// Messaggio 6 Unit temperature statistical information
const msg6: CanMessage = {
  id: 0x04058001, // <-- TODO: sostituisci con l'ID reale
  dir: 'OUT',
  data: Buffer.from([0x00, 0x00, 0x00, 0x00, 0x55]),
  msgType: {
    idType: CAN_ID_TYPE.EXTENDED,
    remote: false,
    canfd: false,
    brs: false
  }
}

// Messaggio 7 Status information 0
const msg7: CanMessage = {
  id: 0x04068001, // <-- TODO: sostituisci con l'ID reale
  dir: 'OUT',
  data: Buffer.from([0x00, 0x00, 0x00, 0x00, 0x74]),
  msgType: {
    idType: CAN_ID_TYPE.EXTENDED,
    remote: false,
    canfd: false,
    brs: false
  }
}


// Messaggio 8 Status information 1
const msg8: CanMessage = {
  id: 0x04078001, // <-- TODO: sostituisci con l'ID reale
  dir: 'OUT',
  data: Buffer.from([0x00, 0x00, 0x00, 0x00, 0x84]),
  msgType: {
    idType: CAN_ID_TYPE.EXTENDED,
    remote: false,
    canfd: false,
    brs: false
  }
}

// Messaggio 9 Status information 2
const msg9: CanMessage = {
  id: 0x04088001, // <-- TODO: sostituisci con l'ID reale
  dir: 'OUT',
  data: Buffer.from([0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88]),
  msgType: {
    idType: CAN_ID_TYPE.EXTENDED,
    remote: false,
    canfd: false,
    brs: false
  }
}

// Messaggio 10 Hardware and battery failure information
const msg10: CanMessage = {
  id: 0x04098001, // <-- TODO: sostituisci con l'ID reale
  dir: 'OUT',
  data: Buffer.from([0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]),
  msgType: {
    idType: CAN_ID_TYPE.EXTENDED,
    remote: false,
    canfd: false,
    brs: false
  }
}

// Messaggio 11 Charging information
const msg11: CanMessage = {
  id: 0x040B8001, // <-- TODO: sostituisci con l'ID reale
  dir: 'OUT',
  data: Buffer.from([0x00, 0x00, 0xAA]),
  msgType: {
    idType: CAN_ID_TYPE.EXTENDED,
    remote: false,
    canfd: false,
    brs: false
  }
}

// Messaggio 12 Limiting
const msg12: CanMessage = {
  id: 0x040D8001, // <-- TODO: sostituisci con l'ID reale
  dir: 'OUT',
  data: Buffer.from([0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDD]),
  msgType: {
    idType: CAN_ID_TYPE.EXTENDED,
    remote: false,
    canfd: false,
    brs: false
  }
}

// Messaggio 13 Limiting
const msg13: CanMessage = {
  id: 0x040E8001, // <-- TODO: sostituisci con l'ID reale
  dir: 'OUT',
  data: Buffer.from([0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDD]),
  msgType: {
    idType: CAN_ID_TYPE.EXTENDED,
    remote: false,
    canfd: false,
    brs: false
  }
}


const WATCHDOG_TIMEOUT = 6000 // 6 secondi

let timer200: NodeJS.Timeout | undefined
let timer500: NodeJS.Timeout | undefined
let timer1000: NodeJS.Timeout | undefined
let watchdog: NodeJS.Timeout | undefined
let started = false

function stopTimers() {
  if (timer200) {
    clearInterval(timer200)
    timer200 = undefined
  }
  if (timer500) {
    clearInterval(timer500)
    timer500 = undefined
  }
  if (timer1000) {
    clearInterval(timer1000)
    timer1000 = undefined
  }
  if (watchdog) {
    clearTimeout(watchdog)
    watchdog = undefined
  }
  started = false
  console.log('Trigger 0x0400FF80 non ricevuto per 6s: timer fermati')
}

function resetWatchdog() {
  if (watchdog) {
    clearTimeout(watchdog)
  }
  watchdog = setTimeout(stopTimers, WATCHDOG_TIMEOUT)
}

Util.Init(async () => {
  console.log('Init: in attesa del messaggio trigger 0x0400FF80')

  Util.OnCan(0x0400FF80, (msg) => {
    resetWatchdog() // ogni volta che arriva il trigger, "ricarico" i 6s

    if (started) return // timer già attivi, non li ricreo
    started = true

    console.log('Trigger 0x0400FF80 ricevuto: avvio i timer')

    timer200 = setInterval(async () => {
      try {
        await output(msg1)
        await output(msg2)
        await output(msg3)
        msg1.id++
        msg2.id++
        msg3.id++
        await output(msg1)
        await output(msg2)
        await output(msg3)
        msg1.id--
        msg2.id--
        msg3.id--
      } catch (error) {
        console.error('Errore invio CAN (200ms):', error)
      }
    }, 200)

    timer500 = setInterval(async () => {
      try {
        await output(msg13)
        msg13.id++
        await output(msg13)
        msg13.id--
      } catch (error) {
        console.error('Errore invio CAN (500ms):', error)
      }
    }, 500)

    timer1000 = setInterval(async () => {
      try {
        await output(msg4)
        await output(msg5)
        await output(msg6)
        await output(msg7)
        await output(msg8)
        await output(msg9)
        await output(msg10)
        await output(msg11)
        await output(msg12)
        msg4.id++
        msg5.id++
        msg6.id++
        msg7.id++
        msg8.id++
        msg9.id++
        msg10.id++
        msg11.id++
        msg12.id++        
        await output(msg4)
        await output(msg5)
        await output(msg6)
        await output(msg7)
        await output(msg8)
        await output(msg9)
        await output(msg10)
        await output(msg11)
        await output(msg12)        
        msg4.id--
        msg5.id--
        msg6.id--
        msg7.id--
        msg8.id--
        msg9.id--
        msg10.id--
        msg11.id--
        msg12.id--               
      } catch (error) {
        console.error('Errore invio CAN (1000ms):', error)
      }
    }, 1000)
  })
})