function greet()
{
    let name = document.querySelector("#name").value;
    alert(`Hello, ${name}`);
}

document.addEventListener('DOMContentLoaded', () =>
{
    document.querySelector('form').addEventListener('submit', greet);
});