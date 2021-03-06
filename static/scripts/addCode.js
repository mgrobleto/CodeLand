'use strict'
import { getCookie } from './libs/cookies.js'
const $form = document.querySelector('#form')
const $nextOption = document.querySelector('#next-option')
const $btnBack = document.querySelector('#btn-back')
const $btnSend = document.querySelector('#btn-send')
const $inputFiles = document.querySelector('#files')
const $listFiles = document.querySelector('#list-files')
const $inputImage = document.querySelector('#input-image')
const $previewImage = document.querySelector('#preview-image')
import { alertError } from './libs/alerts.js'


$form.addEventListener('submit', async (e) => {
    e.preventDefault()

    const formData = new FormData(e.currentTarget)
    formData.set('projectName', formData.get('projectName').normalize('NFD').replace(/[\u0300-\u036f]/g, '').replace(/[\\/:"*?<>|]/g, ''))
    
    console.log(formData.get('project_mode'))

    const barProgress = document.querySelector('#bar-progress')
    barProgress.classList.add('sending')
    
    $btnSend.disabled = true
    $btnSend.innerHTML = 'Enviando...'
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
    } else {
        $btnSend.innerHTML = 'Enviar'
        $btnSend.removeAttribute('disabled')
        alertError(data.message)
    }
    
})

$nextOption.addEventListener('click', (event) => {
    // agregarle la clase .translate y borrar .no-translate a el elemento con clase .form-info-2
    const $formInfo1 = document.querySelector('.project-info-1')
    const $formInfo2 = document.querySelector('.project-info-2')
    $formInfo2.classList.add('no-translate')
    $formInfo1.classList.add('translate')

})

$btnBack.addEventListener('click', (event) => {
    // agregarle la clase .translate y borrar .no-translate a el elemento con clase .form-info-2
    const $formInfo1 = document.querySelector('.project-info-1')
    const $formInfo2 = document.querySelector('.project-info-2')
    $formInfo2.classList.remove('no-translate')
    $formInfo1.classList.remove('translate')

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

$inputImage.addEventListener('change', (event) => {
    const file = $inputImage.files[0]
    const reader = new FileReader()
    reader.onload = (e) => {
        const image = new Image()
        image.src = e.target.result
        $previewImage.appendChild(image)
    }
    reader.readAsDataURL(file)
})

$btnSend.addEventListener('click', (event) => {
    const $projectInfo2 = document.querySelector('.project-info-2')
    // const $projectInfo3 = document.querySelector('.project-info-3')

    $projectInfo2.classList.add('translate')
    // $projectInfo3.classList.add('no-translate')
})
