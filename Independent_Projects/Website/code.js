function content_toggle(element) {
	var button = document.getElementById("display-toggle")
	button.onclick = function() {
		console.log("Attempting to toggle content")
		if (element.style.display == "none"){
			element.style.display = "block";
			button.innerText = "Hide Content"
		} else {
			element.style.display = "none";
			button.innerText = "Show Content"
		}
	}
}