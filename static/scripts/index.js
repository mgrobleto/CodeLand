'use strict'
const $sidenav = document.querySelector('#sidenav')
const $overlay = document.querySelector('#overlay')
const $dropdownBtn = document.querySelector('#dropdown-btn')

if(document.querySelector('#btn-menu')) {
    const $btnMenu = document.querySelector('#btn-menu')
    $overlay.addEventListener('click', () => {
        $sidenav.classList.remove('active')
        $overlay.classList.remove('active')
    })
    
    $btnMenu.addEventListener('click', function() {
        $sidenav.classList.toggle('active')
        $overlay.classList.toggle('active') /* agrega o quita la clase active, la misma clase que activa el menu mobile */
    })
    
    $dropdownBtn.addEventListener('click', () => {
        $dropdownBtn.classList.toggle('active')
    })
}
