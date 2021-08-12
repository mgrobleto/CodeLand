const $form = document.querySelector('#form')
const $registerBtn = document.getElementById('register-btn')

$form.addEventListener('submit', async event => {
    event.preventDefault()
    const formData = new FormData(event.currentTarget)
    formData.set('username', formData.get('username').normalize('NFD').replace(/[\\/:"*?<>|]/g, ''))

    $registerBtn.setAttribute('disabled', false)
    const response = await fetch('/register', {
        method: 'POST',
        body: formData
    })
    const data = await response.json()
    
    if (data.success) {
        window.location.href = '/profile'
    }
        // modal({ message: 'Dimesiones incorrectas, seleccione una image simetrica' })
    
})

function modal({ message }) {
    const $modal = document.getElementById('modal-a')
    const $message = document.getElementById('message')
    $message.innerHTML = message
    $modal.classList.add('active')
}