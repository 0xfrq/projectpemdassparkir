from datetime import datetime

deadline = datetime(2024, 12, 23)

today = datetime.today()

days_left = (deadline - today).days

with open("README.md", "r") as file:
    readme_content = file.read()

updated_readme_content = readme_content.replace("{{DAYS_LEFT}}", str(days_left))

with open("README.md", "w") as file:
    file.write(updated_readme_content)

print(f"Days left until deadline: {days_left}")
