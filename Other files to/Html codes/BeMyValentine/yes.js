function showText() {
    // Get the text element
    var textElement = document.getElementById("textToShow");
    //Get the text element
    var text = document.getElementById("textToHide");

    // Make the text visible
    textElement.style.display = "block";
    //Make the text hidden
    text.style.display = "none";

    // Hide the button after click
    var buttonElement = document.getElementById("myButton");
    //Hide the text after click
    buttonElement.style.display = "none";
    
}

