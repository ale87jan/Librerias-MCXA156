---
name: commit-msg-gen
description: Generate a commit message based on all staged and unstaged changes
disable-model-invocation: false
user-invocable: true
allowed-tools: Bash, Read
---

## Generate Commit Message

Analyze all staged and unstaged changes in the repository to suggest a well-structured commit message following the project's commit conventions.

### Steps

1. Run `git diff` to see unstaged changes and `git diff --cached` to see staged changes.
2. Run `git status` to identify all modified, added, and deleted files.
3. Run `git log --oneline -5` to understand recent commit message style.
4. Read the changed files if needed to understand the context of the modifications.

### Commit Message Format

Follow these conventions strictly:

**Title line**: `type(scope): brief description` (imperative mood, max 50 chars)

Types: `feat`, `fix`, `refactor`, `tune`, `docs`

**Body**: Organized by files changed with bullet points:
- List specific changes per file
- Mark new files with `[NEW]`
- Include parameter changes (old → new) when relevant
- End with an IMPROVEMENTS section summarizing benefits

**Language**: Always English.

### Output

Present the suggested commit message in a code block so the user can review and approve it. Also include a brief summary table of changes per file. Ask the user if they want to proceed with the commit.

**Prefer bash/sed/awk commands for any file operations. Use Python only as a last resort.**
