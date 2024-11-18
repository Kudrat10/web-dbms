const apiUrl = 'http://localhost:3000'; // Change this to your backend URL if different

// Handle registration
document.getElementById('registerForm').addEventListener('submit', async (e) => {
    e.preventDefault(); // Prevent default form submission

    // Get input values
    const username = document.getElementById('registerUsername').value;
    const email = document.getElementById('registerEmail').value;
    const password = document.getElementById('registerPassword').value;

    // Send a POST request to register the user
    const res = await fetch(`${apiUrl}/register`, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ username, email, password })
    });

    // Display response message
    const message = await res.text();
    alert(message); // Show alert with the response message
});

// Handle login
document.getElementById('loginForm').addEventListener('submit', async (e) => {
    e.preventDefault(); // Prevent default form submission

    // Get input values
    const username = document.getElementById('loginUsername').value;
    const password = document.getElementById('loginPassword').value;

    // Send a POST request to login the user
    const res = await fetch(`${apiUrl}/login`, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ username, password })
    });

    const data = await res.json();
    if (res.ok) {
        localStorage.setItem('token', data.token); // Save JWT token
        window.location.href = 'employees.html'; // Redirect to employee management page
    } else {
        alert(data.message); // Display error message
    }
});

// Load employees on the employee management page
if (window.location.pathname.endsWith('employees.html')) {
    loadEmployees();
}

// Handle adding employees
document.getElementById('employeeForm').addEventListener('submit', async (e) => {
    e.preventDefault(); // Prevent default form submission

    // Get input values
    const name = document.getElementById('employeeName').value;
    const position = document.getElementById('employeePosition').value;
    const email = document.getElementById('employeeEmail').value;
    const phone = document.getElementById('employeePhone').value;
    const token = localStorage.getItem('token'); // Get JWT token

    // Send a POST request to add a new employee
    const res = await fetch(`${apiUrl}/employees`, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': token // Include JWT token in headers
        },
        body: JSON.stringify({ name, position, email, phone })
    });

    const message = await res.text(); // Get the response message
    alert(message); // Display response message
    loadEmployees(); // Reload employees after adding
});

// Load employees
async function loadEmployees() {
    const token = localStorage.getItem('token'); // Get JWT token
    const res = await fetch(`${apiUrl}/employees`, {
        headers: {
            'Authorization': token // Include JWT token in headers
        }
    });

    const employees = await res.json(); // Parse the JSON response
    const employeeList = document.getElementById('employeeList');
    employeeList.innerHTML = ''; // Clear existing list

    // Display each employee
    employees.forEach(emp => {
        const li = document.createElement('li');
        li.textContent = `${emp.name} - ${emp.position}`; // Display employee details
        employeeList.appendChild(li); // Add to the list
    });
}
document.getElementById('employeeForm').addEventListener('submit', function(event) {
    event.preventDefault(); // Prevent form submission

    const formData = new FormData(this);
    const data = {
        name: formData.get('name'),
        role: formData.get('role')
    };

    fetch('/api/employees', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(data)
    })
    .then(response => response.json())
    .then(result => {
        console.log(result);
        // Handle success (e.g., show a message or refresh data)
    })
    .catch(error => console.error('Error:', error));
});
app.post('/api/employees', (req, res) => {
    const { name, role } = req.body;

    db.query('INSERT INTO employees (name, role) VALUES (?, ?)', [name, role], (err, results) => {
        if (err) {
            console.error(err);
            return res.status(500).json({ success: false, message: err.message });
        }
        res.json({ success: true, id: results.insertId });
    });
});
