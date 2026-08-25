import { Util, CanMessage, CAN_ID_TYPE, output } from 'ECB'

// Messaggi da 0x701 a 0x705
const messages: CanMessage[] = [0x701, 0x702, 0x703, 0x704, 0x705].map((id) => ({
  id,
  dir: 'OUT',
  data: Buffer.from([0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]), // <-- personalizza il payload
  msgType: {
    idType: CAN_ID_TYPE.STANDARD, // ID standard (11 bit), 0x701-0x705 rientrano nel range
    remote: false,
    canfd: false,
    brs: false
  }
}))

let timer: NodeJS.Timeout | undefined

Util.Init(async () => {
  console.log('Init: avvio invio ciclico ogni 500ms (0x701-0x705)')

  timer = setInterval(async () => {
    try {
      for (const msg of messages) {
        await output(msg)
      }
    } catch (error) {
      console.error('Errore invio CAN:', error)
    }
  }, 500)
})

// opzionale: da chiamare per fermare l'invio periodico
// clearInterval(timer)