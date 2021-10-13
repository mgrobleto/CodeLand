'use strict'
import { getCookie } from './libs/cookies.js'
const $form = document.querySelector('#form')
const $btnSend = document.querySelector('#send-option')
const $inputFiles = document.querySelector('#files')
const $listFiles = document.querySelector('#list-files')

$form.addEventListener('submit', async (e) => {
    e.preventDefault()

    const formData = new FormData(e.currentTarget)
    formData.set('projectName', formData.get('projectName').normalize('NFD').replace(/[\u0300-\u036f]/g, '').replace(/[\\/:"*?<>|]/g, ''))
    
    console.log(formData.get('project_mode'))

    const barProgress = document.querySelector('#bar-progress')
    barProgress.classList.add('sending')
    const response = await fetch('/add-project', {
        method: 'POST',
        body: formData
    })
    const data = await response.json()
    barProgress.classList.remove('sending')
    barProgress.classList.add('sent')
    // const username = getCookie('username')

    console.log(data)
    if (data.success) {
        window.location.pathname = '/profile'
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

$btnSend.addEventListener('click', (e) => {
    $btnSend.innerHTML = '<i class="fas fa-spinner fa-spin"></i>'
})
