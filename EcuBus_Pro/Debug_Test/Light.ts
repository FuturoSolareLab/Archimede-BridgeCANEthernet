import { Util, CanMessage, CAN_ID_TYPE, output } from 'ECB'

const msg: CanMessage = {
  id: 0x400,
  dir: 'OUT',
  data: Buffer.from([0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]), // <-- personalizza il payload
  msgType: {
    idType: CAN_ID_TYPE.STANDARD, // ID standard (11 bit), 0x400 rientra nel range
    remote: false,
    canfd: false,
    brs: false
  }
}

let timer: NodeJS.Timeout | undefined

Util.Init(async () => {
  console.log('Init: avvio invio ciclico ogni 1000ms (0x400)')

  timer = setInterval(async () => {
    try {
      await output(msg)
    } catch (error) {
      console.error('Errore invio CAN:', error)
    }
  }, 1000)
})

// opzionale: da chiamare per fermare l'invio periodico
// clearInterval(timer)