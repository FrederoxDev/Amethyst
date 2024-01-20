export default class CancellationToken {
    private isCancelled: boolean = false;
    public cancel(): void {
        this.isCancelled = true;
    }
  
    public isCancellationRequested(): boolean {
        return this.isCancelled;
    }
}