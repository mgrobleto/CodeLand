import markdown
html = markdown.markdown("""
```javascript
const javascript = 'JavaScript'
```
""")

print(html)