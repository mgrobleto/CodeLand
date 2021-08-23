const $form = document.querySelector('#form')
const $registerBtn = document.getElementById('register-btn')
import { alertError } from './libs/alerts.js'

$form.addEventListener('submit', async event => {
    event.preventDefault()
    const formData = new FormData(event.currentTarget)
    formData.set('username', formData.get('username').normalize('NFD').replace(/[\\/:"*?<>|]/g, ''))

    $registerBtn.setAttribute('disabled', false)
    $registerBtn.innerHTML = 'Registrando...'
    
    const response = await fetch('/register', {
        method: 'POST',
        body: formData
    })
    const data = await response.json()
    console.log(data)
    if (data.success) {
        window.location.href = '/profile'
    } else {
        $registerBtn.removeAttribute('disabled')
        $registerBtn.innerHTML = 'Registrarse'
        alertError(data.message)
    }
        // modal({ message: 'Dimesiones incorrectas, seleccione una image simetrica' })
    
})

function modal({ message }) {
    const $modal = document.getElementById('modal-a')
    const $message = document.getElementById('message')
    $message.innerHTML = message
    $modal.classList.add('active')
}