const $form = document.querySelector('#form')


$form.addEventListener('submit', async event => {
    event.preventDefault()
    const formData = new FormData(event.currentTarget)

    const response = await fetch('/register', {
        method: 'POST',
        body: formData
    })
    if(response.redirected) {
        window.location.href = response.url
    }
  
    
        modal({ message: 'Dimesiones incorrectas, seleccione una image simetrica' })
    
})

function modal({ message }) {
    const $modal = document.getElementById('modal-a')
    const $message = document.getElementById('message')
    $message.innerHTML = message
    $modal.classList.add('active')
}