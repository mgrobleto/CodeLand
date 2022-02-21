'use strict'
import { getCookie } from './libs/cookies.js'
const $form = document.querySelector('#form')
const $btnSend = document.querySelector('#send-option')
const $inputFiles = document.querySelector('#files')
const $listFiles = document.querySelector('#list-files')
import { alertError } from './libs/alerts.js'

$form.addEventListener('submit', async (e) => {
    e.preventDefault();
    console.log('asdsa')

    $btnSend.setAttribute('disabled', 'disabled')
    $btnSend.innerHTML = 'Enviando...'
    
    const formData = new FormData(e.currentTarget)
    formData.set('fragmentName', formData.get('fragmentName').normalize('NFD').replace(/[\u0300-\u036f]/g, '').replace(/[\\/:"*?<>|]/g, ''))
    
    
    const response = await fetch('/add-fragment', {
        method: 'POST',
        body: formData
    })
    const data = await response.json()
    // const username = getCookie('username')
    
    console.log(data)
    if (data.success) {
        window.location.pathname = '/profile'
    } else {
        alertError(data.message)
        $btnSend.removeAttribute('disabled')
        $btnSend.innerHTML = 'Enviar'
    }
    
})

$inputFiles.addEventListener('change', (event) => {
    const files = $inputFiles.files
    if (files.length > 0) {
        const list = document.createElement('ol')
        for(const file of files) {
            const li = document.createElement('li')
            li.innerText = file.name
            list.appendChild(li)
        }
        $listFiles.appendChild(list)
    } else {
        const para = document.createElement('p')
    }
})
