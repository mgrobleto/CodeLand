const $form = document.querySelector('#form')


$form.addEventListener('submit', async event => {
    event.preventDefault()
    const formData = new FormData(event.currentTarget)
    const imageData = formData.get('image')

    console.log(await sizeImage(imageData) && imageData.name !== '')
    if(await sizeImage(imageData) && imageData.name !== '') {
        console.log('entra')
        const response = await fetch('/register', {
            method: 'POST',
            body: formData
        })
        console.log(response)
        if(response.redirected) {
            window.location.href = response.url
        }
    } else {
        modal({ message: 'Dimesiones incorrectas, seleccione una image simetrica' })
    }
})

function modal({ message }) {
    const $modal = document.getElementById('modal-a')
    const $message = document.getElementById('message')
    $message.innerHTML = message
    $modal.classList.add('active')
}

function sizeImage(imageData) {
    return new Promise((resolve, reject) => {
        const image = new Image()
        const url = URL.createObjectURL(imageData)
        image.onload = function () {
            if (this.width === this.height) {
                resolve(true)
            } else {
                resolve(false)
            }
        }
        image.onerr = function () {
            reject('F en el chat')
        }
        image.src = url
    })
}