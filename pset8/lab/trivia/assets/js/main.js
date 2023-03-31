const feedback = document.querySelectorAll('.feedback');

document.addEventListener('DOMContentLoaded', () =>
{

    let correct = document.querySelector('.correct');
    correct.addEventListener('click', correctChoice);

    let wrong = document.querySelectorAll(".wrong");
    wrong.forEach(wrong => {
        wrong.addEventListener('click', () =>
        {
            correct.classList.remove("correct-answer");
            wrong.classList.add("wrong-answer");
            feedback[0].innerHTML = "Incorreto";
        });
    });

    let check = document.querySelector('#check');
    check.addEventListener('click', freeResponse);
});

function correctChoice()
{
    // Caso o usuario escolha a opção certa
    let correct = document.querySelector('.correct');
    let wrong = document.querySelectorAll(".wrong");

    correct.classList.add("correct-answer");
    feedback[0].innerHTML = "Correto";

    wrong.forEach(wrong => {
        wrong.classList.remove("wrong-answer")
    });
}

function freeResponse()
{
    let input = document.querySelector('#name');
    let answer = input.value.toLowerCase();

    if (answer == "roberto dinamite")
    {
        input.style.color = "#4c956c";
        feedback[1].innerHTML = "Correto";
    }
    else
    {
        input.style.color = "#d62828";
        feedback[1].innerHTML = "Incorreto";
    }
}