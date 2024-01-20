import "./SemVersion"
import { SemVersion } from "./SemVersion"

export enum VersionType {
    Release = 0,
    Beta = 1,
    Preview = 2   
};

export class MinecraftVersion {
    version: SemVersion;
    uuid: string;
    versionType: VersionType;

    constructor(version: SemVersion, uuid: string, versionType: VersionType) {
        this.version = version;
        this.uuid = uuid;
        this.versionType = versionType;
    }
}