// templates

export function alertError(message) {
    const $alert = document.querySelector('#error-alert')
    $alert.classList.add('active')
    setTimeout(() => {
        $alert.classList.remove('active')
    }, 4000   )
    $alert.querySelector('#alert-message-text').innerHTML = message
}

export function alertSuccess(message) {
    const $alert = document.querySelector('#success-alert')
    $alert.classList.add('active')
    setTimeout(() => {
        $alert.classList.remove('active')
    }, 4000   )
    $alert.querySelector('#alert-message-text').innerHTML = message
}
