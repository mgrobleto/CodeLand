const loginForm = document.querySelector('#login-form');
const $loginBtn = document.querySelector('#login-btn');
import { alertError } from '/static/scripts/libs/alerts.js'

loginForm.addEventListener('submit', async (e) => {
    e.preventDefault()
    
    const formData = new FormData(loginForm);
    
    $loginBtn.setAttribute('disabled', false);
    const response = await fetch('/login', {
        method: 'POST',
        body: formData
    })
    $loginBtn.innerHTML = 'Logging in...';

    const data = await response.json();
    console.log(data)
    
    if (data.success) {
        window.location.href = '/profile'
    } else {
        $loginBtn.removeAttribute('disabled');
        $loginBtn.innerHTML = 'Ingresar';
        alertError('Datos incorrectos')
    }
})
