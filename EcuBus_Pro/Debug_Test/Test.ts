import { Util } from 'ECB'

let frameCountThisSecond = 0   // contatore frame nel secondo corrente
let maxFramesPerSecond = 0     // massimo numero di frame/sec osservato
let minFramesPerSecond: number | undefined = undefined // minimo numero di frame/sec osservato

let lastLoggedMax: number | undefined = undefined
let lastLoggedMin: number | undefined = undefined

// Conta tutti i frame CAN ricevuti (in e out), qualunque sia l'ID
Util.OnCan(true, (msg) => {
  frameCountThisSecond++
})

// Ogni secondo: calcola i frame/sec e aggiorna max/min
setInterval(() => {
  const count = frameCountThisSecond
  frameCountThisSecond = 0 // reset per il prossimo secondo

  if (count > maxFramesPerSecond) {
    maxFramesPerSecond = count
  }

  if (minFramesPerSecond === undefined || count < minFramesPerSecond) {
    minFramesPerSecond = count
  }
}, 1000)

// Ogni 10 secondi: scrive sul log SOLO se max o min sono cambiati dall'ultimo log
setInterval(() => {
  const maxChanged = maxFramesPerSecond !== lastLoggedMax
  const minChanged = minFramesPerSecond !== lastLoggedMin

  if (maxChanged || minChanged) {
    console.log(
      `[Frame Stats] Max frame/sec: ${maxFramesPerSecond} | Min frame/sec: ${minFramesPerSecond}`
    )
    lastLoggedMax = maxFramesPerSecond
    lastLoggedMin = minFramesPerSecond
  }
}, 10000)

Util.Init(() => {
  console.log('Init: monitoraggio frame/sec avviato (max/min loggati ogni 10s se aggiornati)')
})