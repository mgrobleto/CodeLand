const loginForm = document.querySelector('#login-form');

loginForm.addEventListener('submit', async (e) => {
    e.preventDefault()
    
    const formData = new FormData(loginForm);
    
    const response = await fetch('/login', {
        method: 'POST',
        body: formData
    })
    const data = await response.json();
    
    if (data.success) {
        window.location.href = '/profile'
    }
})
