const VERSION = 'v1'

self.addEventListener('install', event => {
    event.waitUntil(precache())
    console.log('instalado')
})

self.addEventListener('fetch', event => {
    const request = event.request
    if(request.method !== 'GET') {
        return;
    }
    event.responseWith(cacheResponse(request))
})

async function precache() {
    const cache = await caches.open(VERSION)
    return cache.addAll([
        '/',
        '/static/scripts/index.js',
        '/static/images/background.webp',
        '/static/images/Logos.png',
        '/static/style.css',
        '/static/styles/components/header.css'
    ])
}

async function cacheResponse(request) {
    const cache = await caches.open(VERSION)
    const response = await cache.match(request)
    return response || fetch(request)
}
