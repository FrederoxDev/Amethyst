export class SemVersion {
    major: number;
    minor: number;
    patch: number;
    build: number;

    constructor(major: number, minor: number, patch: number, build: number) {
        this.major = major;
        this.minor = minor;
        this.patch = patch;
        this.build = build;
      }
    
    toString(): string {
        return `${this.major}.${this.minor}.${this.patch}.${this.build}`;
    }
}