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

    static fromString(versionString: string): SemVersion | null {
        const versionRegex = /^(\d+)\.(\d+)\.(\d+)\.(\d+)$/;
        const match = versionString.match(versionRegex);
    
        if (match) {
          const [, major, minor, patch, build] = match.map(Number);
          return new SemVersion(major, minor, patch, build);
        }
    
        console.error('Invalid version string format');
        return null;
      }
}