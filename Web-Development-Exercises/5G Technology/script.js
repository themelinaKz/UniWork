window.onload = function () {
    init();
    navBarFocus(window.location.href);

    //minAge();
    var list = Array.prototype.slice.call(document.querySelectorAll("input"));
    list.push(document.getElementById("sports"));

    if(list[0]!=null){
        // add listeners to all input fields
        for (let i = 0; i < list.length; i++) {
            let e = list[i];

            // show textfield if other ch_other is checked
            if (e.id == "ch_other") {
                e.addEventListener("change", textFieldVisibility);
            }
            // ignore
            if (['button', 'checkbox', 'radio', 'submit'].includes(e.type)) continue;

            // password matching
            if (e.id == "passwordConfirm") {
                e.addEventListener("input", function (event) {
                    let pc = event.target;
                    let p = list[i - 1];
                    let error = document.querySelector("#" + pc.id + " + .warning");
                    error.innerHTML = "";
                    pc.className = "";
                    pc.style.borderColor = "";
                    if (p.value != null && event.target.value != p.value.substring(event.target.length)) {
                        error.innerHTML = "Οι κωδικοί δεν ταιριάζουν.";
                        p.className = "input-warning-pass";
                        pc.className = "input-warning-pass";
                        pc.style.borderColor = "red";
                    }
                    else {
                        p.className = "";
                    }
                });
            }

            // set the right pattern
            if (e.id == "github") e.pattern = "[a-zA-Z]{1}([a-zA-Z0-9]|-|_)*";
            switch (e.type) {
                case "text": e.pattern = "[α-ωΑ-Ωa-zA-Zίϊΐόάέύϋΰήώ]{1}[α-ωΑ-Ωa-zA-Zίϊΐόάέύϋΰήώ ]*"; break;
                case "number": e.pattern = "[0-9]+"; break;
                case "tel": e.pattern = "\\+?[0-9]+"; break;
            }

            // add input listeners to cut input if it overflows
            e.addEventListener("input", function (event) {
                event.target.className = "";
            })

            // add onblur listeners
            e.addEventListener("blur", function (event) {
                if (event.target.value != null && e.id != "passwordConfirm") {
                    event.preventDefault();
                    checkValidity(event.target);
                }
            });

            // add focus listeners
            e.addEventListener("focus", function (event) {
                document.querySelector("#" + event.target.id + " + .warning").innerHTML = "";
            });
        }

        document.getElementById("submit").addEventListener("click", function (event) {
            //check all inputs
            for (let e of list) {
                if (!['checkbox', 'radio', 'submit'].includes(e.type)) {
                    checkValidity(e);
                }
            }
            //check checkbox group
            document.querySelector("#otherLanguages .warning").innerHTML = groupCompleted("otherLanguages");
            //check textarea input
            checkValidity(document.getElementById("sports"));
            //check radio group
            document.querySelector("#whatEnd .warning").innerHTML = groupCompleted("whatEnd");
        });

        // add change listener to each checkbox to remove warning if any
        let checkboxes = document.querySelectorAll("#otherLanguages input");
        for (let box of checkboxes) {
            box.addEventListener("change", function (b) {
                let error = document.querySelector("#otherLanguages .warning");
                let field = document.getElementById("lang_other");
                error.style.visibility = "hidden";
                if (b.target.checked) {
                    if (!(b.target.id == "ch_other" && field.value.trim().length == 0)) {
                        error.innerHTML = "";
                    }
                    else if (b.target.id == "ch_other") {
                        field.required = true;
                        error.style.visibility = "visible";
                        field.focus();
                    }
                }
                else if (b.target.id == "ch_other") {
                    field.required = false;
                }
            });
        }

        // add change listener to each radio button to remove warning if any
        let radios = document.querySelectorAll("#whatEnd input");
        for (let radio of radios) {
            radio.addEventListener("change", function (r) {
                var error = document.querySelector("#whatEnd .warning");
                if (r.target.checked) {
                    error.innerHTML = "";
                }
            });
        }
    }
}

/**Checks if at least one element is checked in checkbox and radio groups
 * @param {string} g the name of the group
 * @returns the text of the warning if there's any
 */
function groupCompleted(g) {
    let inputs = document.querySelectorAll("#" + g + " input");
    let flag = false;
    for (let i = 0; i < inputs.length; i++) {
        if (inputs[i].checked) {
            console.log(inputs[i].id);
            if (inputs[i].id == "ch_other") {
                if (inputs[i + 1].value.trim().length != 0 && inputs[i + 1].value != null) {
                    flag = true;
                    break;
                }
                else continue;
            }
            flag = true;
            break;
        }
    }
    if (!flag) {
        if (g == "otherLanguages") return "Πρέπει να επιλέξετε τουλάχιστον μία γλώσσα.";
        else return "Το πεδίο είναι υποχρεωτικό.";
    }
    return "";
}

function init() {
    // configure date and color
    dayColor = dayColor();

    // update 
    let date = document.getElementById("date");
    date.innerHTML = dayColor[0];

    // update colors
    updateColors(dayColor[1]);
}

/** Enables focus on tab of current webpage */
function navBarFocus(location) {
    let file = String(location).substring(String(location).lastIndexOf("/") + 1, location.length - 5);
    var tabs = document.querySelectorAll("nav a");
    switch (file) {
        case "index": tabs[0].focus(); break;
        case "history": tabs[1].focus(); break;
        case "future": tabs[2].focus(); break;
    }
}

/** Updates footer, asides and date element colors */
function updateColors(color) {
    // set Color of Date
    date.style.color = color;
    date.style.borderColor = color;

    // set background of asides
    let asides = document.querySelectorAll("aside");
    let size = asides.length;
    for (let i = 0; i < size; i++) {
        asides[i].style.background = color;
    }

    // set background of the footer
    document.querySelectorAll("footer")[0].style.background = color;
}

/** Configures date element and color */
function dayColor() {
    let date = new Date();
    let day_n = date.getDay()
    const months = ["Ιανουαρίου", "Φεβρουαρίου", "Μαρτίου", "Απριλίου", "Μαΐου", "Ιουνίου", "Ιουλίου", "Αυγούστου", "Σεπτεβρίου", "Οκτωβρίου", "Νοεμβρίου", "Δεκεμβρίου"];

    var day, color;
    switch (day_n) {
        case 0:
            day = "Κυριακή";
            color = "rgb(224, 139, 139)"; break;
        case 1:
            day = "Δευτέρα";
            color = "rgb(218, 132, 175)"; break;
        case 2:
            day = "Τρίτη";
            color = "rgb(172, 233, 86)"; break;
        case 3:
            day = "Τετάρτη"
            color = "rgb(139, 224, 163)"; break;
        case 4:
            day = "Πέμπτη";
            color = "rgb(86, 189, 233)"; break;
        case 5:
            day = "Παρασκευή";
            color = " rgb(158, 143, 241)"; break;
        case 6:
            day = "Σάββατο";
            color = "rgb(143, 197, 241)"; break;
        default:
            day = "Nice Day";
    }
    return [day + ", " + date.getDate() + " " + months[date.getMonth()], color];
}

/** Shows confirm popup to visit external website */
function hrefClicked() {
    let c = confirm("Πρόκειται να μεταφερθείτε σε εξωτερική ιστοσελίδα. Συνέχεια;");
    if (!c) return false;
}

/** Changes quote in future.html file */
function changeQuote() {
    const quotes = ["\"My project was retarded by laws of nature. The world was not prepared for it. It was <em>too far ahead of time</em>. But the same laws will prevail the end and make it a \
                    <em>triumphal success</em>... The future will show whether my foresight is as accurate now as it has proven heretofore\"",
        "\"When <em>wireless</em> is perfectly applied the whole earth will be converted into a <em>huge brain</em>, which in fact it is, all <em>things</em> being particles of a real \
                    and rhythmic whole.\"" ];

    let current = document.querySelector("#quote");
    if (current.innerHTML == quotes[0])
        current.innerHTML = quotes[1];
    else current.innerHTML = quotes[0];
}

/** Adds 2nd or 3rd phone field, based on what is already visible */
function addPhone() {
    let phone2 = document.getElementById("phone2");
    let addPhone1 = document.getElementById("addPhone1");
    var addPhone2 = document.getElementById("addPhone2");
    var removePhone2 = document.getElementById("removePhone2");
    if (phone2.style.visibility == "hidden") {
        let phoneIn2 = document.getElementById("phoneIn2");
        phone2.style.visibility = "visible";
        addPhone1.style.visibility = "hidden";
        addPhone2.style.visibility = "visible";
        removePhone2.style.visibility = "visible";
        phoneIn2.required = true;
    }
    else {
        let phoneIn3 = document.getElementById("phoneIn3");
        document.getElementById("phone3").style.visibility = "visible";
        addPhone2.style.visibility = "hidden";
        removePhone2.style.visibility = "hidden";
        phoneIn3.required = true;
    }
}

/** Removes 2nd or 3rd phone field, based on the parameter */
function removePhone(phone) {
    var addPhone2 = document.getElementById("addPhone2");
    var removePhone2 = document.getElementById("removePhone2");
    if (phone == 2) {
        let phone2 = document.getElementById("phone2");
        phone2.style.visibility = "hidden";
        phone2.required = false;
        addPhone2.style.visibility = "hidden";
        removePhone2.style.visibility = "hidden";
        document.getElementById("addPhone1").style.visibility = "visible";
    }
    else {
        let phone3 = document.getElementById("phone3");
        phone3.style.visibility = "hidden";
        phone3.required = false;
        addPhone2.style.visibility = "visible";
        removePhone2.style.visibility = "visible";
    }
}

/** Adds 2nd language field */
function addLanguage() {
    let language2 = document.getElementById("language2");
    document.getElementById("addLanguage1").style.visibility = "hidden";
    document.getElementById("language_2").style.visibility = "visible";
    language2.required = true;
}

/** Removes 2nd language field */
function removeLanguage() {
    document.getElementById("language2").required = false;
    document.getElementById("addLanguage1").style.visibility = "visible";
    document.getElementById("language_2").style.visibility = "hidden";
}

/** If the 'favorite language' input exists in 'other languages' group,
 *  this input is chacked and disabled in the checkbox group */
function updateProgLanguages() {
    let list = document.getElementById("progLanguages").options;
    var input = document.getElementById("progLanguage").value.toLowerCase();
    var datalist = document.querySelectorAll("#otherLanguages input");
    if (input == "c++") input = "cpp";
    else if (input == "c#") input = "cSharp";

    // set all checkboxes to unchecked
    for (let i = 0; i < datalist.length; i++) {
        datalist[i].checked = false;
        datalist[i].disabled = false;
    }
    // check checkbox if input exists in datalist
    for (let i = 0; i < list.length; i++) {
        if (list[i].id == input) {
            let checkbox = document.getElementById("lang_" + input);
            checkbox.checked = true;
            checkbox.disabled = true;
        }
    }
}

/** Called onchange of checkbox ch_other, so that when checkbox is checked textfield appears, 
 * overwise it hides*/
function textFieldVisibility(event) {
    var lang_other = document.getElementById("lang_other");

    // If the checkbox is checked, show text field
    if (event.target.checked) {
        lang_other.style.visibility = "visible";
        lang_other.required = true;
    }
    else {
        lang_other.style.visibility = "hidden";
        lang_other.value = "";
        lang_other.required = false;
    }
}

/**Checks whether 'sports' textarea is valid
 * @returns false if any special character or number is found */
function sportsIsValid() {
    var text = document.getElementById("sports").value.split("\n");
    let matches;
    for (let i = 0; i < text.length; i++) {
        matches = text[i].match("[α-ωΑ-Ωa-zA-Zίϊΐόάέύϋΰήώ ]*");
        if (matches == null || matches[0] != text[i]) {
            return false;
        }
    }
    return true;
}

/** Finds minimum age user should have (as birthDate) */
function minAge() {
    var date = new Date();
    var minDate = new Date(date.getFullYear() - 18, date.getMonth(), date.getDate());
    minDate.setDate(minDate.getDate() - 1)
    return minDate;
}

/** Prints possible warnings of 'field' input field */
function checkValidity(field) {
    let error = document.querySelector("#" + field.id + " + .warning");
    error.innerHTML = "";
    let flag = false;
    if (field.id == "sports" && !sportsIsValid()) {
        field.previousElementSibling.open = true;
        field.setCustomValidity("Συμπληρώστε το πεδίο όπως προβλέπουν οι οδηγίες");
        error.innerHTML = "Συμπληρώστε το πεδίο όπως προβλέπουν οι οδηγίες";
        flag = true;
    }
    else if (field.type == "date" && new Date(field.value) > minAge()) {
        field.setCustomValidity("Πρέπει να είστε άνω των 18 ετών");
        error.innerHTML = "Η συνεισφορά είναι διαθέσιμη μόνο για άτομα άνω των 18 ετών.";
        flag = true;
    }
    else if (field.validity.valueMissing) {
        flag = true;
        if (['phoneIn2', 'phoneIn3', 'language2', 'lang_other'].includes(field.id)) {
            if (field.required && field.style.visibility == "visible") {
                field.setCustomValidity("Συμπληρώστε το πεδίο, διαφορετικά αφαιρέστε το.");
                error.innerHTML = "Αν δεν θέλετε να συμπληρώσετε τελικά το πεδίο παρακαλώ αφαιρέστε το."
            }
        }
        else {
            field.setCustomValidity("Παρακαλώ συμπληρώστε το πεδίο.");
            error.innerHTML = "Το πεδίο είναι υποχρεωτικό.";
        }
    }
    else if (field.validity.typeMismatch || field.validity.badInput) {
        flag = true;
        switch (field.type) {
            case "number":
            case "tel":
                field.setCustomValidity("Επιτρέπονται μόνο αριθμοί.")
                error.innerHTML = "Μόνο νούμερα απ'το 0 έως και το 9 επιτρέπονται."; break;
            case "email":
                field.setCustomValidity("Το email που δηλώσατε δεν έχει σωστή μορφή. (example@mail.com)")
                error.innerHTML = "Το email πρέπει να είναι της μορφής 'example@mail.com'."; break;
        }
    }
    else if (field.validity.tooShort) {
        flag = true;
        field.setCustomValidity("Μη έγκυρος κωδικός. Χρειάζονται τουλάχιστον 7 χαρακτήρες");
        error.innerHTML = "Οι κωδικοί πρέπει να αποτελούνται από τουλάχιστον 7 χαρακτήρες."
    }
    else if (field.validity.tooLong) {
        flag = true;
        switch (field.id) {
            case "firstName":
            case "lastName":
                field.setCustomValidity("Επιτρέπονται μέχρι 30 χαρακτήρες.");
                error.innerHTML = "Το πεδίο μπορεί να αποτελείται το πολύ από 30 χαρακτήρες."; break;
            case "phoneIn1":
            case "phoneIn2":
            case "phoneIn3":
            case "lang_other":
                field.setCustomValidity("Επιτρέπονται μέχρι 15 χαρακτήρες.");
                error.innerHTML = "Το πεδίο μπορεί να αποτελείται το πολύ από 15 χαρακτήρες."; break;
            case "username":
                field.setCustomValidity("Επιτρέπονται μέχρι 20 χαρακτήρες");
                error.innerHTML = "Το πεδίο μπορεί να αποτελείται το πολύ από 20 χαρακτήρες."; break;
        }
    }
    else if (field.validity.patternMismatch) {
        flag = true;
        // if input is just whitespaces
        if (field.value.trim().length == 0) {
            if (['phoneIn2', 'phoneIn3', 'language2', 'lang_other'].includes(field.id)) {
                field.setCustomValidity("Συμπληρώστε το πεδίο, διαφορετικά αφαιρέστε το.");
                error.innerHTML = "Αν δεν θέλετε να συμπληρώσετε τελικά το πεδίο παρακαλώ αφαιρέστε το."
            }
            else {
                field.setCustomValidity("Παρακαλώ συμπληρώστε το πεδίο.");
                error.innerHTML = "Το πεδίο είναι υποχρεωτικό.";
            }
            return;
        }
        switch (field.id) {
            case "sports":
                document.querySelector(".current").previousElementSibling.open = true;
                field.setCustomValidity("Συμπληρώστε το πεδίο όπως προβλέπουν οι οδηγίες");
                error.innerHTML = "Συμπληρώστε το πεδίο όπως προβλέπουν οι οδηγίες"; break;
            case "github":
                field.setCustomValidity("Συμπληρώστε το username του GitHub σας, όπως φαίνεται στο URL του λογαριασμού σας.");
                error.innerHTML = "Επιτρέπονται μόνο αγγλικοί χαρακτήρες, αριθμοί, παύλες και κάτω παύλες. \
                                   Το 1ο στοιχείο πρέπει να είναι γράμμα."; break;
        }
        if (!['sports', 'github'].includes(field.id)) {
            switch (field.type) {
                case "text":
                    field.setCustomValidity("Επιτρέπονται μόνο ελληνικά και λατινικά γράμματα.");
                    error.innerHTML = "Ειδικοί χαρακτήρες και αριθμοί δεν επιτρέπονται, μόνο γράμματα."; break;
                case "tel":
                    field.setCustomValidity("Επιτρέπονται μόνο αριθμοί και προαιρετικά 1 φορά το σύμβολο '+΄' στην αρχή.");
                    error.innerHTML = "Επιτρέπονται μόνο αριθμοί και το σύμβολο + στην αρχή εφόσον είναι απαραίτητο."; break;
                case "number":
                    field.setCustomValidity("Επιτρέπονται μόνο αριθμοί");
                    error.innerHTML = "Επιτρέπονται μόνο αριθμοί."; break;
            }
        }
    }
    if (flag) {
        field.className = "input-warning";
    }
}
